#include "function/complexe_polygon.h"

void createRectangle(float width, float height, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
    vertices.reserve(4);
    indices.reserve(6);
    const float HALF_WIDTH = width / 2.f;
    const float HALF_HEIGHT = height / 2.f;
    vertices.push_back(Vertex(-HALF_WIDTH, -HALF_HEIGHT, 0, 0, 0, 1, 0, 0));
    vertices.push_back(Vertex( HALF_WIDTH, -HALF_HEIGHT, 0, 0, 0, 1, 1, 0));
    vertices.push_back(Vertex( HALF_WIDTH,  HALF_HEIGHT, 0, 0, 0, 1, 1, 1));
    vertices.push_back(Vertex(-HALF_WIDTH,  HALF_HEIGHT, 0, 0, 0, 1, 0, 1));
    indices = { 0,1,2,0,2,3 };
}

void createCube(float width, float height, float depth, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
    vertices.reserve(24);
    indices.reserve(36);
    // top face
    vertices.push_back(Vertex(bdm::Vector3f(-width / 2.f, -height / 2.f, -depth / 2.f), bdm::Vector3f(0, -1, 0), bdm::Vector2f(0.25, 0)));
    vertices.push_back(Vertex(bdm::Vector3f( width / 2.f, -height / 2.f, -depth / 2.f), bdm::Vector3f(0, -1, 0), bdm::Vector2f(0.5 , 0)));
    vertices.push_back(Vertex(bdm::Vector3f( width / 2.f, -height / 2.f,  depth / 2.f), bdm::Vector3f(0, -1, 0), bdm::Vector2f(0.5 , 0.25)));
    vertices.push_back(Vertex(bdm::Vector3f(-width / 2.f, -height / 2.f,  depth / 2.f), bdm::Vector3f(0, -1, 0), bdm::Vector2f(0.25, 0.25)));

    // down face
    vertices.push_back(Vertex(bdm::Vector3f(-width / 2.f,  height / 2.f, -depth / 2.f), bdm::Vector3f(0, 1, 0), bdm::Vector2f(0.25, 0.75)));
    vertices.push_back(Vertex(bdm::Vector3f( width / 2.f,  height / 2.f, -depth / 2.f), bdm::Vector3f(0, 1, 0), bdm::Vector2f(0.5 , 0.75)));
    vertices.push_back(Vertex(bdm::Vector3f( width / 2.f,  height / 2.f,  depth / 2.f), bdm::Vector3f(0, 1, 0), bdm::Vector2f(0.5 , 0.5)));
    vertices.push_back(Vertex(bdm::Vector3f(-width / 2.f,  height / 2.f,  depth / 2.f), bdm::Vector3f(0, 1, 0), bdm::Vector2f(0.25, 0.5)));

    // left face
    vertices.push_back(Vertex(bdm::Vector3f(-width / 2.f, -height / 2.f, -depth / 2.f), bdm::Vector3f(-1, 0, 0), bdm::Vector2f(0   , 0.25)));
    vertices.push_back(Vertex(bdm::Vector3f(-width / 2.f,  height / 2.f, -depth / 2.f), bdm::Vector3f(-1, 0, 0), bdm::Vector2f(0   , 0.5)));
    vertices.push_back(Vertex(bdm::Vector3f(-width / 2.f,  height / 2.f,  depth / 2.f), bdm::Vector3f(-1, 0, 0), bdm::Vector2f(0.25, 0.5)));
    vertices.push_back(Vertex(bdm::Vector3f(-width / 2.f, -height / 2.f,  depth / 2.f), bdm::Vector3f(-1, 0, 0), bdm::Vector2f(0.25, 0.25)));

    // right face
    vertices.push_back(Vertex(bdm::Vector3f( width / 2.f, -height / 2.f, -depth / 2.f), bdm::Vector3f(1, 0, 0), bdm::Vector2f(0.75, 0.25)));
    vertices.push_back(Vertex(bdm::Vector3f( width / 2.f,  height / 2.f, -depth / 2.f), bdm::Vector3f(1, 0, 0), bdm::Vector2f(0.75, 0.5)));
    vertices.push_back(Vertex(bdm::Vector3f( width / 2.f,  height / 2.f,  depth / 2.f), bdm::Vector3f(1, 0, 0), bdm::Vector2f(0.5 , 0.5)));
    vertices.push_back(Vertex(bdm::Vector3f( width / 2.f, -height / 2.f,  depth / 2.f), bdm::Vector3f(1, 0, 0), bdm::Vector2f(0.5 , 0.25)));

    // back face
    vertices.push_back(Vertex(bdm::Vector3f(-width / 2.f, -height / 2.f, -depth / 2.f), bdm::Vector3f(0, 0, -1), bdm::Vector2f(0.25, 1)));
    vertices.push_back(Vertex(bdm::Vector3f( width / 2.f, -height / 2.f, -depth / 2.f), bdm::Vector3f(0, 0, -1), bdm::Vector2f(0.5 , 1)));
    vertices.push_back(Vertex(bdm::Vector3f( width / 2.f,  height / 2.f, -depth / 2.f), bdm::Vector3f(0, 0, -1), bdm::Vector2f(0.5 , 0.75)));
    vertices.push_back(Vertex(bdm::Vector3f(-width / 2.f,  height / 2.f, -depth / 2.f), bdm::Vector3f(0, 0, -1), bdm::Vector2f(0.25, 0.75)));

    // front face
    vertices.push_back(Vertex(bdm::Vector3f(-width / 2.f, -height / 2.f,  depth / 2.f), bdm::Vector3f(0, 0, 1), bdm::Vector2f(0.25, 0.25)));
    vertices.push_back(Vertex(bdm::Vector3f( width / 2.f, -height / 2.f,  depth / 2.f), bdm::Vector3f(0, 0, 1), bdm::Vector2f(0.5 , 0.25)));
    vertices.push_back(Vertex(bdm::Vector3f( width / 2.f,  height / 2.f,  depth / 2.f), bdm::Vector3f(0, 0, 1), bdm::Vector2f(0.5 , 0.5)));
    vertices.push_back(Vertex(bdm::Vector3f(-width / 2.f,  height / 2.f,  depth / 2.f), bdm::Vector3f(0, 0, 1), bdm::Vector2f(0.25, 0.5)));

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(3);

    indices.push_back(4);
    indices.push_back(5);
    indices.push_back(6);
    indices.push_back(4);
    indices.push_back(6);
    indices.push_back(7);

    indices.push_back(8);
    indices.push_back(9);
    indices.push_back(10);
    indices.push_back(8);
    indices.push_back(10);
    indices.push_back(11);

    indices.push_back(12);
    indices.push_back(13);
    indices.push_back(14);
    indices.push_back(12);
    indices.push_back(14);
    indices.push_back(15);

    indices.push_back(16);
    indices.push_back(17);
    indices.push_back(18);
    indices.push_back(16);
    indices.push_back(18);
    indices.push_back(19);

    indices.push_back(20);
    indices.push_back(21);
    indices.push_back(22);
    indices.push_back(20);
    indices.push_back(22);
    indices.push_back(23);
}

void createTorus(float global_radius, float section_radius, int point, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
    vertices.reserve((point + 1) * (point + 1));
    indices.reserve(6 * point * point);
    bdm::Vector3f center, circle_point;
    // Vertices
    for (int j = 0; j < point + 1; j++)
    {
        center.set(global_radius * cosf(2 * j * M_PI / (point)), global_radius * sinf(2 * j * M_PI / (point)), 0);
        for (int i = 0; i < point + 1; i++)
        {
            vertices.push_back(Vertex());
            circle_point.x = cosf(2 * j * M_PI / (point)) * (global_radius + section_radius * cosf(2 * i * M_PI / (point)));
            circle_point.y = sinf(2 * j * M_PI / (point)) * (global_radius + section_radius * cosf(2 * i * M_PI / (point)));
            circle_point.z = section_radius * sinf(2 * i * M_PI / (point));
            // Coordinates
            vertices.back().position.set(circle_point.x, circle_point.y, circle_point.z);
            circle_point -= center;
            circle_point.normalize();
            // Normals
            vertices.back().normal.set(circle_point.x, circle_point.y, circle_point.z);
            // Texture coord
            vertices.back().texture_coords.set(j / float(point), i / float(point));
        }
    }
    // Indices
    for (int j = 0; j < point; j++)
    {
        for (int i = 0; i < point; i++)
        {
            indices.push_back(j * (point + 1) + i);
            indices.push_back(j * (point + 1) + i + 1);
            indices.push_back((j + 1) * (point + 1) + i);

            indices.push_back(j * (point + 1) + i + 1);
            indices.push_back((j + 1) * (point + 1) + i);
            indices.push_back((j + 1) * (point + 1) + i + 1);
        }
    }
}

void createCircle(float radius, int point, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
    vertices.reserve(point);
    indices.reserve(point + 1);
    for (int i = 0; i < point; i++)
    {
        bdm::Vector3f position(radius * cos(2 * i * M_PI / (point)), radius * sin(2 * i * M_PI / (point)), 0);
        bdm::Vector3f normal(position);
        normal.normalize();
        vertices.push_back(Vertex(position, normal, bdm::Vector2f()));
        indices.push_back(i);
    }
    vertices.push_back(0);
}

void createCylinder(float height, float radius, int point, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, float proportion)
{
    const int POINT = point * proportion;
    indices.reserve(12 * POINT);
    vertices.reserve(2 * (2 * POINT + 1));
    int ind = 0;
    bdm::Vector3f center, p, p_norm;
    // vertices for the disk
    for (int h = -1; h < 2; h = h + 2)
    {
        float half_height = height / 2 * h;
        center.set(0, 0, half_height);
        bdm::Vector2f texture_circle_center_ = bdm::Vector2f(0.5 + (0.25 * h), 0.75);
        vertices.push_back(Vertex(center, bdm::Vector3f(0, 0, h), texture_circle_center_));
        for (int i = 0; i < POINT + 1; i++)
        {
            p.x = radius * cosf(2 * i * M_PI / (point));
            p.y = radius * sinf(2 * i * M_PI / (point));
            p.z = half_height;
            vertices.push_back(Vertex(p, bdm::Vector3f(0, 0, h), texture_circle_center_ + bdm::Vector2f(cosf(2 * i * M_PI / (point)), sinf(2 * i * M_PI / (point))) * 0.25));
        }
        // indices for the disks
        for (int i = 1; i < POINT + 1; i++)
        {
            indices.push_back(ind * (2 + POINT));
            indices.push_back(ind * (2 + POINT) + i);
            indices.push_back(ind * (2 + POINT) + i + 1);
        }
        ind++;
    }
    // border
    for (int h = -1; h < 2; h = h + 2)
    {
        float half_height = height / 2 * h;
        center.set(0, 0, half_height);

        for (int i = 0; i < POINT + 1; i++)
        {
            p.x = radius * cosf(2 * i * M_PI / (point));
            p.y = radius * sinf(2 * i * M_PI / (point));
            p.z = half_height;
            p_norm = p - center;
            p_norm.normalize();
            vertices.push_back(Vertex(p, p_norm, bdm::Vector2f(i/float(point), 0.25 + (h * 0.25))));
        };
    }
    const unsigned int SECOND_DISKS_POINT_START = 2 * (POINT + 2);
    // indices for the outer layer
    for (int i = 0; i < POINT; i++)
    {
        indices.push_back(SECOND_DISKS_POINT_START + i);
        indices.push_back(SECOND_DISKS_POINT_START + i + 1);
        indices.push_back(SECOND_DISKS_POINT_START + (POINT + 1) + i);

        indices.push_back(SECOND_DISKS_POINT_START + i + 1);
        indices.push_back(SECOND_DISKS_POINT_START + (POINT + 1) + i);
        indices.push_back(SECOND_DISKS_POINT_START + (POINT + 1) + i + 1);
    }
}

void createCone(float height, float radius, int point, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
    vertices.reserve(3 * point + 2);// a faire correspondre
    indices.reserve(6 * point); // à faire correspondre
    float half_height = height / 2.f;
    bdm::Vector3f center(0, 0, -half_height), p;
    //base circle center
    vertices.push_back(Vertex(center, bdm::Vector3f(0, 0, -1), bdm::Vector2f(0.75, 0.25)));

    const float CENTER_ANGLE = M_PI / 2.f - atan(height / radius);
    const float SMALL_TRIG_ANGLE = radius * cos(CENTER_ANGLE);
    const  float P_X = SMALL_TRIG_ANGLE * sin(M_PI / 2.f - CENTER_ANGLE);
    const  float P_Y = SMALL_TRIG_ANGLE * cos(M_PI / 2.f - CENTER_ANGLE);
    float x, y, z;
    z = -half_height + P_Y;
    //base circle point
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < point; i++)
        {
            vertices.push_back(Vertex());
            p.x = radius * cosf(2 * i * M_PI / (point));
            p.y = radius * sinf(2 * i * M_PI / (point));
            p.z = -half_height;

            vertices.back().position.set(p);

            if (j == 0)
            {
                p.x = P_X * cosf(2 * i * M_PI / (point));
                p.y = P_X * sinf(2 * i * M_PI / (point));
                p.z = z;
                p -= center;
                p.normalize();
                vertices.back().normal.set(p);
                vertices.back().texture_coords.set(0.25 + 0.25 * cosf(2 * i * M_PI / (point)), 0.25 + 0.25 * sinf(2 * i * M_PI / (point)));
            }
            else
            {
                vertices.back().normal.set(0, 0, -1);
                vertices.back().texture_coords.set(0.75 + 0.25 * cosf(2 * i * M_PI / (point)), 0.25 + 0.25 * sinf(2 * i * M_PI / (point)));
            }
        }
    }
    for (int i = 0; i < point; i++)
    {
        p.x = P_X * cosf(2 * (i + 1 / 2.f) * M_PI / (point));
        p.y = P_X * sinf(2 * (i + 1 / 2.f) * M_PI / (point));
        p.z = z;

        p -= center;
        p.normalize();
        vertices.push_back(Vertex(bdm::Vector3f(0, 0, half_height), p, bdm::Vector2f(0.25, 0.25)));
    }

    for (int i = 1; i < point; i++)
    {
        indices.push_back(0);
        indices.push_back(point + i);
        indices.push_back(point + i + 1);

        indices.push_back(2 * point + i);
        indices.push_back(i);
        indices.push_back(i + 1);
    }
    indices.push_back(0);
    indices.push_back(point + 1 + point - 1);
    indices.push_back(point + 1);

    indices.push_back(2 * point + point);
    indices.push_back(point);
    indices.push_back(1);
}

void createPyramid(float height, float base_half_size, int point, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
    vertices.reserve(4 * point + 1);// a faire correspondre
    indices.reserve(6 * point); // à faire correspondre
    float half_height = height / 2.f;
    bdm::Vector3f center(0, 0, -half_height), p;
    vertices.push_back(Vertex(center, bdm::Vector3f(0, 0, -1), bdm::Vector2f(0.75, 0.25)));

    for (int i = 0; i < point; i++)
    {
        p.x  = base_half_size * cosf(2 * i * M_PI / (point));
        p.y = base_half_size * sinf(2 * i * M_PI / (point));
        p.z = -half_height;

        vertices.push_back(Vertex(p, bdm::Vector3f(0, 0, -1), bdm::Vector2f(0.75 + 0.25 * cosf(2 * i * M_PI / (point)), 0.25 + 0.25 * sinf(2 * i * M_PI / (point)))));
    }
    for (int i = 1; i < point; i++)
    {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }
    indices.push_back(0);
    indices.push_back(point);
    indices.push_back(1);
    unsigned int vert_start = vertices.size();
    const float CENTER_ANGLE = M_PI / 2.f - atan(height / base_half_size);
    const float SMALL_TRIG_ANGLE = base_half_size * cos(CENTER_ANGLE);
    const  float P_X = SMALL_TRIG_ANGLE * sin(M_PI / 2.f - CENTER_ANGLE);
    const  float P_Y = SMALL_TRIG_ANGLE * cos(M_PI / 2.f - CENTER_ANGLE);
    float z;
    z = -half_height + P_Y;
    bdm::Vector3f norm, norm2;
    for (int i = 0; i < point; i++)
    {
        norm.x = P_X * cosf(2 * i * M_PI / float(point));
        norm.y = P_X * sinf(2 * i * M_PI / float(point));
        norm.z = z;

        norm2.x = P_X * cosf(2 * (i + 1) * M_PI / float(point));
        norm2.y = P_X * sinf(2 * (i + 1) * M_PI / float(point));
        norm2.z = z;

        norm = (norm + norm2) / 2.f;
        norm -= center;
        norm.normalize();
        p.x = base_half_size * cosf(2 * i * M_PI / float(point));
        p.y = base_half_size * sinf(2 * i * M_PI / float(point));
        p.z = -half_height;

        vertices.push_back(Vertex(p, norm, bdm::Vector2f(0.25 + 0.25 * cosf(2 * i * M_PI / (point)), 0.25 + 0.25 * sinf(2 * i * M_PI / (point)))));

        p.x = base_half_size * cosf(2 * (i + 1) * M_PI / float(point));
        p.y = base_half_size * sinf(2 * (i + 1) * M_PI / float(point));
        p.z = -half_height;

        vertices.push_back(Vertex(p, norm, bdm::Vector2f(0.25 + 0.25 * cosf(2 * (i + 1) * M_PI / (point)), 0.25 + 0.25 * sinf(2 * (i + 1) * M_PI / (point)))));

        p.set(0, 0, half_height);

        vertices.push_back(Vertex(p, norm, bdm::Vector2f(0.25, 0.25)));

        indices.push_back(vert_start);
        indices.push_back(vert_start + 1);
        indices.push_back(vert_start + 2);
        vert_start += 3;
    }
}

void createSphere(float radius, int segments, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, float proportion)
{
    vertices.reserve((segments + 1) * int(segments * proportion + 1));
    indices.reserve(6 * segments * int(segments * proportion));
    constexpr float PI2 = 2.0 * M_PI;
    bdm::Vector3f point;
    // vertices generation
    for (int lat = 0; lat < segments + 1; lat++) {
        float theta = lat * M_PI / segments;
        float sinTheta = std::sin(theta);
        float cosTheta = std::cos(theta);

        for (int lon = 0; lon < int(segments * proportion + 1); lon++) {
            float phi = lon * PI2 / segments;
            float sinPhi = std::sin(phi);
            float cosPhi = std::cos(phi);

            vertices.push_back(Vertex());

            // Coordinates
            point.x = radius * sinTheta * cosPhi;
            point.y = radius * sinTheta * sinPhi;
            point.z = radius * cosTheta;
            vertices.back().position.set(point);

            // Normals
            point.normalize();
            vertices.back().normal.set(point);

            // Texture coords
            vertices.back().texture_coords.set(lon / float(segments * proportion), lat / float(segments));
        }
    }

    // indices generation
    for (int lat = 0; lat < segments; lat++)
    {
        for (int lon = 0; lon < int(segments * proportion); lon++) 
        {
            int current = lat * int(segments * proportion + 1) + lon;
            int next = current + int(segments * proportion + 1);

            indices.push_back(current);
            indices.push_back(next);
            indices.push_back(current + 1);

            indices.push_back(next);
            indices.push_back(next + 1);
            indices.push_back(current + 1);
        }
    }
}

void createTerrainSphere(float radius, int segments, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, float proportion)
{
    vertices.reserve((segments + 1) * int(segments * proportion + 1));
    indices.reserve(6 * segments * int(segments * proportion));
    constexpr float PI2 = 2.0 * M_PI;
    constexpr float TERRAIN_PROP = 0.5f;
    bdm::Vector3f point;
    // vertices generation
    for (int lat = 0; lat < int(segments * proportion + 1); lat++) {
        float theta = lat * M_PI / segments;
        float sinTheta = std::sin(theta);
        float cosTheta = std::cos(theta);

        for (int lon = 0; lon < int(segments * TERRAIN_PROP + 1); lon++) {
            float phi = lon * PI2 / segments;
            float sinPhi = std::sin(phi);
            float cosPhi = std::cos(phi);

            vertices.push_back(Vertex());

            // Coordinates
            point.x = radius * sinTheta * cosPhi;
            point.y = radius * sinTheta * sinPhi;
            point.z = radius * cosTheta;
            vertices.back().position.set(point);

            // Normals
            point.normalize();
            vertices.back().normal.set(point);

            // Texture coords
            vertices.back().texture_coords.set(lon / float(segments * TERRAIN_PROP), lat / float(segments * proportion));
        }
    }

    // indices generation
    for (int lat = 0; lat < int(segments * proportion); lat++)
    {
        for (int lon = 0; lon < int(segments * TERRAIN_PROP); lon++)
        {
            int current = lat * int(segments * TERRAIN_PROP + 1) + lon;
            int next = current + int(segments * TERRAIN_PROP + 1);

            indices.push_back(current);
            indices.push_back(next);
            indices.push_back(current + 1);

            indices.push_back(next);
            indices.push_back(next + 1);
            indices.push_back(current + 1);
        }
    }
}
