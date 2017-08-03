import sys
from PIL import Image
import numpy as np
import numpy.linalg as la
from abc import ABC
from random import random
import time
from threading import Thread


sys.setrecursionlimit(10000)


def normalize(v):
    return v / la.norm(v)


def random_in_unit_sphere():
    p = np.ones(3)
    while la.norm(p)**2 >= 1:
        p = np.random.uniform(-1, 1, 3)
    return p


class Ray(object):
    def __init__(self, p, direction):
        self.p = p
        self.direction = direction

    def __str__(self):
        return f"<{self.p}, {self.direction}>"

    def point_at_parameter(self, t):
        return self.p + t * self.direction


class ReflectionRecord(object):
    def __init__(self, status, r, attenuation):
        self.status = status
        self.r = r
        self.attenuation = attenuation


class Material(ABC):
    def scatter(self, r_in, rec):
        """ return a scattered ray and attenuation """


class Lambertian(Material):
    def __init__(self, albedo):
        self.albedo = albedo

    def scatter(self, r_in, rec):
        scattered = Ray(rec.p_hit, rec.normal + random_in_unit_sphere())
        return ReflectionRecord(True, scattered, self.albedo)


def reflect(v, n):
    return v - 2 * (v@n) * n


class Metal(Material):
    def __init__(self, albedo, fuzz=0.0):
        self.albedo = albedo
        self.fuzz = fuzz

    def scatter(self, r_in, rec):
        reflected = reflect(normalize(r_in.direction), rec.normal)
        scattered = Ray(rec.p_hit,
                        reflected + self.fuzz * random_in_unit_sphere())
        return ReflectionRecord(scattered.direction @ rec.normal > 0,
                                scattered,
                                self.albedo)


class RefractionRecord(object):
    def __init__(self, status, r):
        self.status = status
        self.r = r


def refract(v, n, ni_over_nt):
    uv = normalize(v)
    dt = uv @ n
    discriminant = 1.0 - (ni_over_nt**2) * (1 - dt**2)
    if discriminant > 0:
        return RefractionRecord(True,
                                ni_over_nt * (uv - n * dt) -
                                n * np.sqrt(discriminant))
    else:
        return RefractionRecord(False, None)


def schlick(cosine, ref_idx):
    r0 = (1 - ref_idx) / (1 + ref_idx)
    r0 **= 2
    return r0 + (1 - r0) * (1 - cosine)**5


class Dielectric(Material):
    def __init__(self, ref_idx):
        self.ref_idx = ref_idx

    def scatter(self, r_in, rec):
        outward_normal = None
        reflected = reflect(r_in.direction, rec.normal)
        ni_over_nt = None
        attenuation = np.array([1, 1, 1])
        refracted = None

        reflect_prob = None
        cosine = None

        if r_in.direction @ rec.normal > 0:
            outward_normal = -rec.normal
            ni_over_nt = self.ref_idx
            cosine = self.ref_idx * \
                (r_in.direction @ rec.normal) / la.norm(r_in.direction)
        else:
            outward_normal = rec.normal
            ni_over_nt = 1 / self.ref_idx
            cosine = -(r_in.direction @ rec.normal) / la.norm(r_in.direction)

        refracted = refract(r_in.direction, outward_normal, ni_over_nt)
        if refracted.status:
            reflect_prob = schlick(cosine, self.ref_idx)
        else:
            return ReflectionRecord(True,
                                    Ray(rec.p_hit, reflected),
                                    attenuation)

        if random() < reflect_prob:
            return ReflectionRecord(True,
                                    Ray(rec.p_hit, reflected),
                                    attenuation)
        else:
            return ReflectionRecord(True,
                                    Ray(rec.p_hit, refracted.r),
                                    attenuation)


class HitRecord(object):
    def __init__(self, status, t_hit, p_hit, normal, material):
        self.status = status
        self.t_hit = t_hit
        self.p_hit = p_hit
        self.normal = normal
        self.material = material


class Collideable(ABC):
    def hit_by(self, r, t_min, t_max):
        """ Returns information about when/if self is hit by ray r """


class Plane(Collideable):
    def __init__(self, origin, normal, material):
        self.origin = origin
        self.normal = normal
        self.material = material

    def hit(self, r, t_min, t_max):
        if r.direction @ self.normal == 0:
            return HitRecord(False, None, None, None, None)
        else:
            t = ((self.origin - r.p) @ self.normal) / (r.direction @ self.normal)
            if t_min < t < t_max:
                p = r.point_at_parameter(t)
                n = self.normal
                return HitRecord(True, t, p, n, self.material)
            else:
                return HitRecord(False, None, None, None, None)


class Sphere(Collideable):
    def __init__(self, center, radius, material):
        self.center = center
        self.radius = radius
        self.material = material

    def __str__(self):
        return f"<{self.center}, {self.radius}, {self.material}>"

    def hit(self, r, t_min, t_max):
        oc = r.p - self.center
        a = r.direction @ r.direction
        b = 2 * (r.direction @ oc)
        c = oc @ oc - self.radius**2
        discriminant = b**2 - 4 * a * c
        if discriminant > 0:
            first_root = (-b - np.sqrt(discriminant)) / (2 * a)
            if t_min < first_root < t_max:
                t = first_root
                p = r.point_at_parameter(first_root)
                n = (p - self.center) / self.radius
                return HitRecord(True, t, p, n, self.material)
            second_root = (-b + np.sqrt(discriminant)) / (2 * a)
            if t_min < second_root < t_max:
                t = second_root
                p = r.point_at_parameter(second_root)
                n = (p - self.center) / self.radius
                return HitRecord(True, t, p, n, self.material)
        return HitRecord(False, None, None, None, None)


class World(object):
    def __init__(self, *objs):
        self.objs = objs

    def hit(self, r, t_min, t_max):
        rec = HitRecord(False, None, None, None, None)
        cur_closest = t_max
        for obj in self.objs:
            temp_rec = obj.hit(r, t_min, cur_closest)
            if temp_rec.status:
                cur_closest = temp_rec.t_hit
                rec = temp_rec
        return rec


def random_in_unit_disk():
    p = np.ones(3)
    while la.norm(p) >= 1:
        x = np.random.uniform(-1, 1)
        y = np.random.uniform(-1, 1)
        p = np.array([x, y, 0])
    return p


class Camera(object):
    def __init__(self, lookfrom, lookat, vup, vfov, aspect,
                 aperture, focus_dist):

        theta = vfov * np.pi / 180
        half_height = np.tan(theta / 2)
        half_width = aspect * half_height

        self.lens_radius = aperture / 2

        self.origin = lookfrom
        self.w = normalize(lookfrom - lookat)
        self.u = normalize(np.cross(vup, self.w))
        self.v = np.cross(self.w, self.u)
        self.lower_left = self.origin - \
            self.u * focus_dist * half_width - \
            self.v * focus_dist * half_height - \
            self.w * focus_dist
        self.horizontal = 2 * half_width * self.u * focus_dist
        self.vertical = 2 * half_height * self.v * focus_dist
        # self.lower_left = np.array([-half_width, -half_height, -1])
        # self.horizontal = np.array([2 * half_width, 0, 0])
        # self.vertical = np.array([0, 2*half_height, 0])
        # self.origin = np.zeros(3)

    def get_ray(self, s, t):
        rd = self.lens_radius * random_in_unit_disk()
        offset = self.u * rd[0] + self.v * rd[1]
        return Ray(self.origin + offset,
                   self.lower_left +
                   s * self.horizontal +
                   t * self.vertical -
                   self.origin - offset)


def color(r, world, depth):
    rec = world.hit(r, 1e-5, 1e9)
    if rec.status:
        ref_rec = rec.material.scatter(r, rec)
        if depth < 25 and ref_rec.status:
            return ref_rec.attenuation * color(ref_rec.r,
                                               world,
                                               depth + 1)
        else:
            return np.zeros(3)
    else:
        return np.ones(3)

if __name__ == "__main__":
    nx, ny = 200, 100
    lookfrom = np.array([0, .5, -1])
    lookat = np.array([0, .5, 0])
    vup = np.array([0, 1, 0])
    vfov = 90
    aspect_ratio = nx / ny
    aperture = 0
    focus_dist = la.norm(lookfrom - lookat)
    c = Camera(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, focus_dist)

    ns = 50

    r, g, b = [np.zeros((ny, nx)) for _ in range(3)]
    gamma = 2

    spheres = []

    spheres.append(Sphere(np.array([0, .5, 0]),
                          0.5,
                          Lambertian(np.array([0.1, 0.5, 0.7]))))

    w = World(*spheres,
              Plane(np.zeros(3), np.array([0, 1, 0]),
                    Lambertian(np.array([.8, .8, .8]))))

    def process_pixel(i, j):
        col = np.zeros(3)
        for s in range(ns):
            u = (i + random()) / nx
            v = 1 - ((j + random()) / ny)
            col += color(c.get_ray(u, v), w, 0)
        col /= ns
        col **= 1 / gamma
        r[j, i] = col[0]
        g[j, i] = col[1]
        b[j, i] = col[2]

    axes = np.ogrid[0: nx, 0: ny]
    coords = np.dstack(np.meshgrid(axes[0], axes[1])).reshape(-1, 2)
    timesum = 0.0
    t1 = time.time()
    for n, (i, j) in enumerate(coords):
        if n % nx == 0:
            t2 = time.time()
            timesum += (t2-t1)
            print(n // nx, f"{t2-t1}", f"{timesum}")
            t1 = t2
        process_pixel(i, j)
    img = np.dstack((r, g, b))
    Image.fromarray(np.uint8(img * 255)).save("test4.png")
