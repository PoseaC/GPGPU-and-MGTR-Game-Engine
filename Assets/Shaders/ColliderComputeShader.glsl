#version 430 core

layout(local_size_x = 256) in;

struct ColliderDataBuffer
{
    vec3 position;
    vec3 velocity;
    vec3 boxSize;
    float mass;
    int isKinematic;
    int isTrigger;
    float elasticity;
    float friction;
    float drag;
    float gravity;
    float deltaTime;
};

layout(std430, binding = 0) buffer ColliderBuffer
{
    ColliderDataBuffer colliders[];
};

void main()
{
	float epsilon = 0.0001f;
    uint i = gl_GlobalInvocationID.x;
    if (i >= colliders.length()) return;

    ColliderDataBuffer c = colliders[i];

    if (c.isKinematic == 1) return;

    // gravity and drag
    c.velocity += vec3(0, -c.gravity * c.mass, 0) * c.deltaTime;
    c.velocity *= (1.0 - c.drag);

    // collision checking
    for (uint j = 0; j < colliders.length(); j++)
    {
        if (i == j) continue;

        ColliderDataBuffer other = colliders[j];

        vec3 thisMax = c.position + c.boxSize;
        vec3 thisMin = c.position - c.boxSize;
        vec3 otherMax = other.position + other.boxSize;
        vec3 otherMin = other.position - other.boxSize;

        bool isOverlapping = (thisMax.x > otherMin.x - epsilon && thisMax.y > otherMin.y - epsilon && thisMax.z > otherMin.z + epsilon) &&
		                    (thisMin.x < otherMax.x + epsilon && thisMin.y < otherMax.y + epsilon && thisMin.z < otherMax.z - epsilon); 

        if (isOverlapping)
        {
            if (c.isTrigger == 1) return;

            vec3 collisionNormal = normalize(other.position - c.position);
            float relativeVelocity = dot(c.velocity - other.velocity, collisionNormal);

            if (relativeVelocity < 0)
            { // collision response
                float j = -(1 + c.elasticity) * relativeVelocity / (1 / c.mass + 1 / other.mass);

                c.velocity += (j / c.mass) * collisionNormal;
                other.velocity += (j / other.mass) * -collisionNormal;
            }
        }
    }

    c.position += c.velocity * c.deltaTime;

    colliders[i] = c;
}
