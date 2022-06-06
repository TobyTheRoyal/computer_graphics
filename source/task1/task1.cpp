#include <limits>

#include "Scene.h"

#include "task1.h"
#include "math.h"
#include "vector"

constexpr float epsilon = 0.0001f;
#define FULL_VERSION
const triangle_t* findClosestHit(const float3& p, const float3& d,
    const triangle_t* triangles,
    std::size_t num_triangles,
    const float3* vertices, float& t,
    float& lambda_1, float& lambda_2) {
    float lambda_1_tmp;
    float lambda_2_tmp;
    float t_tmp;

    float closest_lambda_1;
    float closest_lambda_2;
    float closest_t = 1000000.0f;
    triangle_t* closestTriangle = nullptr;

    for (int n = 0; n < num_triangles; n++) {

        math::vector<float, 3> p1 = vertices[triangles[0][0]];
        math::vector<float, 3> p2 = vertices[triangles[0][1]];
        math::vector<float, 3> p3 = vertices[triangles[0][2]];

        math::vector<float, 3> e1 = p2 - p1;
        math::vector<float, 3> e2 = p3 - p1;
        math::vector<float, 3> q = p - p1;

        const float qx = q.y * e1.z - q.z * e1.y;
        const float qy = q.z * e1.x - q.x * e1.z;
        const float qz = q.x * e1.y - q.y * e1.x;
        math::vector<float, 3> qe1;
        qe1.x = qx;
        qe1.y = qy;
        qe1.z = qz;

        const float dx = d.y * e2.z - d.z * e2.y;
        const float dy = d.z * e2.x - d.x * e2.z;
        const float dz = d.x * e2.y - d.y * e2.x;
        math::vector<float, 3> de2;
        de2.x = dx;
        de2.y = dy;
        de2.z = dz;

        float de2DOTe1 = de2.x * e1.x + de2.y * e1.y + de2.z * e1.z;
        float qe1DOTe2 = qe1.x * e2.x + qe1.y * e2.y + qe1.z * e2.z;
        float de2DOTq = de2.x * q.x + de2.y * q.y + de2.z * q.z;
        float qe1DOTd = qe1.x * d.x + qe1.y * d.y + qe1.z * d.z;

        if (de2DOTe1 != 0) {
            lambda_1_tmp = de2DOTq / de2DOTe1;
            lambda_2_tmp = qe1DOTd / de2DOTe1;
            t_tmp = qe1DOTe2 / de2DOTe1;

            if (lambda_1_tmp >= 0 && lambda_2_tmp >= 0 && (lambda_1_tmp + lambda_2_tmp) <= 1) {
                if (t_tmp < closest_t)
                {
                    closest_t = t_tmp;
                    closest_lambda_1 = lambda_1_tmp;
                    closest_lambda_2 = lambda_2_tmp;
                    closestTriangle = const_cast<triangle_t*>(triangles);
                }
            }
        }
        triangles++;
    }
    if (closestTriangle != nullptr) {
        t = closest_t;
        lambda_1 = closest_lambda_1;
        lambda_2 = closest_lambda_2;
        return closestTriangle;
    }
  // TODO: implement intersection test between a ray and a set of triangles.
  // This function should find the CLOSEST intersection with a triangle along
  // the ray. The ray is given by its start point p and direction d. A triangle
  // is represented as an array of three vertex indices. The position of each
  // vertex can be looked up from the vertex array via the vertex index.
  // triangles points to the first element of an array of num_triangles
  // triangles. If an intersection is found, set t to the ray parameter and
  // lambda_1 and lambda_2 to the barycentric coordinates corresponding to the
  // closest point of intersection, and return a pointer to the hit triangle.
  // If no intersection is found, return nullptr.

  return nullptr;
}

bool intersectsRay(const float3& p, const float3& d,
                   const triangle_t* triangles, std::size_t num_triangles,
                   const float3* vertices, float t_min, float t_max) {

  // TODO: implement intersection test between a ray and a set of triangles.
  // This method only has to detect whether there is an intersection with ANY
  // triangle along the given subset of the ray. The ray is given by its start
  // point p and direction d. A triangle is represented as an array of three
  // vertex indices. The position of each vertex can be looked up from the
  // vertex array via the vertex index. triangles points to an array of
  // num_triangles. If an intersection is found that falls on a point on the ray
  // between t_min and t_max, return true. Otherwise, return false.
    for (int n = 0; n < num_triangles; n++) {

        math::vector<float, 3> p1 = vertices[triangles[0][0]];
        math::vector<float, 3> p2 = vertices[triangles[0][1]];
        math::vector<float, 3> p3 = vertices[triangles[0][2]];

        math::vector<float, 3> e1 = p2 - p1;
        math::vector<float, 3> e2 = p3 - p1;
        math::vector<float, 3> q = p - p1;

        const float qx = q.y * e1.z - q.z * e1.y;
        const float qy = q.z * e1.x - q.x * e1.z;
        const float qz = q.x * e1.y - q.y * e1.x;
        math::vector<float, 3> qe1;
        qe1.x = qx;
        qe1.y = qy;
        qe1.z = qz;

        const float dx = d.y * e2.z - d.z * e2.y;
        const float dy = d.z * e2.x - d.x * e2.z;
        const float dz = d.x * e2.y - d.y * e2.x;
        math::vector<float, 3> de2;
        de2.x = dx;
        de2.y = dy;
        de2.z = dz;

        float de2DOTe1 = de2.x * e1.x + de2.y * e1.y + de2.z * e1.z;
        float qe1DOTe2 = qe1.x * e2.x + qe1.y * e2.y + qe1.z * e2.z;
        float de2DOTq = de2.x * q.x + de2.y * q.y + de2.z * q.z;
        float qe1DOTd = qe1.x * d.x + qe1.y * d.y + qe1.z * d.z;
        float lambda_1;
        float lambda_2;
        float t;
        if (de2DOTe1 != 0) {

            t = qe1DOTe2 / de2DOTe1;
            if (t <= t_max && t >= t_min) {
                lambda_1 = de2DOTq / de2DOTe1;
                lambda_2 = qe1DOTd / de2DOTe1;

                if (lambda_1 >= 0 && lambda_2 >= 0 && (lambda_1 + lambda_2) <= 1) {
                    return true;
                }
            }

        }
        triangles++;

    }
  return false;
}

float3 shade(const float3& p, const float3& d, const HitPoint& hit,
             const Scene& scene, const Pointlight* lights,
             std::size_t num_lights) {

    math::vector<float, 3> pixel_color = { 0,0,0 };

    for (int s = 0; s < num_lights; s++) {

        math::vector<float,3> l_buffer = lights[s].position - hit.position;
        float divisor_l = sqrt(l_buffer.x * l_buffer.x + l_buffer.y * l_buffer.y + l_buffer.z * l_buffer.z);
        math::vector<float, 3> l;
        l.x = (l_buffer.x / divisor_l);
        l.y = (l_buffer.y / divisor_l);
        l.z = (l_buffer.z / divisor_l);

        float t_max = length(l);
        float divisor_v = sqrt(d.x * d.x + d.y * d.y + d.z * d.z);
        math::vector<float,3> v;
        v.x = (d.x / divisor_v);
        v.y = (d.y / divisor_v);
        v.z = (d.z / divisor_v);

        float divisor_n = sqrt(hit.normal.x * hit.normal.x + hit.normal.y * hit.normal.y + hit.normal.z * hit.normal.z);
        math::vector<float, 3> n;
        n.x = hit.normal.x / divisor_n;
        n.y = hit.normal.y / divisor_n;
        n.z = hit.normal.z / divisor_n;

        float cos_theta = n.x * l.x + n.y * l.y + n.z * l.z;
        math::vector<float,3> cd = std::max((float)0,cos_theta) * hit.k_d;
        math::vector<float, 3> r_buffer = 2 * cos_theta * n - l;
        float divisor_r = sqrt(r_buffer.x * r_buffer.x + r_buffer.y * r_buffer.y + r_buffer.z * r_buffer.z);
        math::vector<float, 3> r;
        r.x = (r_buffer.x / divisor_r);
        r.y = (r_buffer.y / divisor_r);
        r.z = (r_buffer.z / divisor_r);

        if (cos_theta <= 0) {
            math::vector<float, 3> cs = { 0,0,0 };
        }
        else {
            math::vector<float, 3> h_buffer = v + l;
            float divisor_h = sqrt(h_buffer.x * h_buffer.x + h_buffer.y * h_buffer.y + h_buffer.z * h_buffer.z);
            math::vector<float, 3> h;
            h.x = (h_buffer.x / divisor_h);
            h.y = (h_buffer.y / divisor_h);
            h.z = (h_buffer.z / divisor_h);
            float cos_alpha = hit.normal.x * h.x + hit.normal.y * h.y + hit.normal.z * h.z;
            math::vector<float, 3> cs = hit.k_s * pow((std::max((float)0, cos_alpha)),hit.m);

            math::vector<float,3> shadow_point = hit.position + hit.normal * epsilon;
            math::vector<float, 3> s_buffer = lights[s].position - shadow_point;
            float divisor_s = sqrt(s_buffer.x * s_buffer.x + s_buffer.y * s_buffer.y + s_buffer.z * s_buffer.z);
            math::vector<float, 3> shadow_dir;
            shadow_dir.x = (s_buffer.x / divisor_s);
            shadow_dir.y = (s_buffer.y / divisor_s);
            shadow_dir.z = (s_buffer.z / divisor_s);

            if (scene.intersectsRay(shadow_point, shadow_dir, 0, 1000) == true) {
                continue;
            }
            math::vector<float,3> L = cd + cs;

            pixel_color.x = pixel_color.x + (L.x * lights[s].color.x);
            pixel_color.y = pixel_color.y + (L.y * lights[s].color.y);
            pixel_color.z = pixel_color.z + (L.z * lights[s].color.z);
        }

    }
    return pixel_color;
  // TODO: implement phong shading.
  // hit represents the surface point to be shaded.
  // hit.position, hit.normal, and hit.k_d and hit.k_s contain the position,
  // surface normal, and diffuse and specular reflection coefficients,
  // hit.m the specular power.
  // lights is a pointer to the first element of an array of num_lights
  // point light sources to consider.
  // Each light contains a member to give its position and color.
  // Return the shaded color.

  // To implement shadows, use scene.intersectsRay(p, d, t_min, t_max) to test
  // whether a ray given by start point p and direction d intersects any
  // object on the section between t_min and t_max.

}

void render(image2D<float3>& framebuffer, int left, int top, int right,
            int bottom, const Scene& scene, const Camera& camera,
            const Pointlight* lights, std::size_t num_lights,
            const float3& background_color, int max_bounces) {



  // TODO: implement raytracing, render the given portion of the framebuffer.
  // left, top, right, and bottom specify the part of the image to compute
  // (inclusive left, top and exclusive right and bottom).
  // camera.eye, camera.lookat, and camera.up specify the position and
  // orientation of the camera, camera.w_s the width of the image plane,
  // and camera.f the focal length to use.
  // Use scene.findClosestHit(p, d) to find the closest point where the ray
  // hits an object.
  // The method returns an std::optional<HitPoint>.
  // If an object is hit, call the function shade to compute the color value
  // of the HitPoint illuminated by the given array of lights.
  // If the ray does not hit an object, use background_color.

  // BONUS: extend your implementation to recursive ray tracing.
  // max_bounces specifies the maximum number of secondary rays to trace.
    const math::vector<float, 3> origin = camera.eye;
    const math::vector<float, 3> w_buffer = camera.eye - camera.lookat;
    const float divisor_w = sqrt(w_buffer.x * w_buffer.x + w_buffer.y * w_buffer.y + w_buffer.z * w_buffer.z);
    math::vector<float, 3> w;
    w.x = (w_buffer.x / divisor_w);
    w.y = (w_buffer.y / divisor_w);
    w.z = (w_buffer.z / divisor_w);

    const float cx = camera.up.y * w.z - camera.up.z * w.y;
    const float cy = camera.up.z * w.x - camera.up.x * w.z;
    const float cz = camera.up.x * w.y - camera.up.y * w.x;
    math::vector<float, 3> c;
    c.x = cx;
    c.y = cy;
    c.z = cz;

    const float divisor_u = sqrt(c.x * c.x + c.y * c.y + c.z * c.z);
    math::vector<float, 3> u;
    u.x = (c.x / divisor_u);
    u.y = (c.y / divisor_u);
    u.z = (c.z / divisor_u);

    math::vector<float, 3> v;
    v.x = w.y * u.z - w.z * u.y;
    v.y = w.z * u.x - w.x * u.z;
    v.z = w.x * u.y - w.y * u.x;
    float aspect_ratio = height(framebuffer)/(float)width(framebuffer);
    float h_s = aspect_ratio * camera.w_s;

  for (int y = top; y < bottom; ++y) {
      for (int x = left; x < right; ++x) {

          float ud = ((x * camera.w_s) /width(framebuffer)) - camera.w_s/2;
          float vd = (h_s / 2) - (y * h_s / height(framebuffer));

          math::vector<float, 3> direction = ud * u + vd * v - camera.f * w;

          std::optional<HitPoint> hit_point = scene.findClosestHit(origin, direction);
          if (hit_point = scene.findClosestHit(origin,direction))
              framebuffer(x, y) = shade(origin,direction,*hit_point,scene,lights,num_lights);
          else
              framebuffer(x, y) = background_color;
    }
  }
}
