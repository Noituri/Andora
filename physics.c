#include "physics.h"
#include "raymath.h"

void PositionalCorrection(Manifold *m)
{
	PObject *A = m->A;
	PObject *B = m->B;

	const float percent = 0.2f;
	const float slop = 0.01f;
	float tmp = (max(m->penetration - slop, 0.0f) / (A->invMass + B->invMass)) * percent;
	Vector2 correction = Vector2Scale(m->normal, tmp);
	A->position = Vector2Subtract(A->position, Vector2Scale(correction, A->invMass));
	B->position = Vector2Add(B->position, Vector2Scale(correction, B->invMass));
}

void ResolveCollision(Manifold *m)
{
	PObject *A = m->A;
	PObject *B = m->B;

	Vector2 relativeV = Vector2Subtract(B->velocity, A->velocity);
	float velAlongNormal = Vector2DotProduct(relativeV, m->normal);
	if (velAlongNormal > 0)
		return;

	if(A->mass == 0)
		A->invMass = 0;
	else
		A->invMass = 1 / A->mass;

	if(B->mass == 0)
		B->invMass = 0;
	else
		B->invMass = 1 / B->mass;

	float e = min(A->restitution, B->restitution);
	float j = -(e + 1) * velAlongNormal;

	j /= 1 / A->mass + 1 / B->mass;

	Vector2 impulse = Vector2Scale(m->normal, j);
	float massSum = A->mass + B->mass;

	float ratio = A->mass / massSum;
	A->velocity = Vector2Subtract(A->velocity, Vector2Scale(impulse, ratio));

	ratio = B->mass / massSum;
	B->velocity = Vector2Add(B->velocity, Vector2Scale(impulse, ratio));
}

int AABBvsAABB(Manifold *m)
{
	Vector2 normal = Vector2Subtract(m->B->position, m->A->position);
	float aExtent = (m->A->aabb.max.x - m->A->aabb.min.x) / 2;
	float bExtent = (m->B->aabb.max.x - m->B->aabb.min.x) / 2;

	float xOverlap = aExtent + bExtent - fabsf(normal.x);
	if (xOverlap > 0) {
		float aExtent = (m->A->aabb.max.y - m->A->aabb.min.y) / 2;
		float bExtent = (m->B->aabb.max.y - m->B->aabb.min.y) / 2;

		float yOverlap = aExtent + bExtent - fabsf(normal.y);
		if (yOverlap > 0) {
			if (xOverlap > yOverlap) {
				if (normal.x < 0)
					m->normal = (Vector2) {-1, 0};
				else
					m->normal = Vector2Zero();
				m->penetration = xOverlap;
			} else {
				if (normal.y < 0)
					m->normal = (Vector2) {0, -1};
				else
					m->normal = (Vector2) {0, 1};
				m->penetration = yOverlap;
			}

			return 1;
		}
	}

	return 0;
}