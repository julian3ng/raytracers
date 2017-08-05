open Core
   
module Vec3 = struct
  type vec3 = {x:float; y:float; z:float}
  let create_vec3 (x:float) (y:float) (z:float) = {x=x; y=y; z=z}
  let add (u:vec3) (v:vec3) = {x=u.x+.v.x; y=u.y+.v.y; z=u.z+.v.z}
  let sum (vs:vec3 list) = List.fold_left vs ~init:{x=0.; y=0.; z=0.} ~f:add
  let sub (u:vec3) (v:vec3) = {x=u.x-.v.x; y=u.y-.v.y; z=u.z-.v.z}
  let mul (u:vec3) (v:vec3) = {x=u.x*.v.x; y=u.y*.v.y; z=u.z*.v.z}
  let div (u:vec3) (v:vec3) = {x=u.x/.v.x; y=u.y/.v.y; z=u.z/.v.z}
  let addf (u:vec3) (f:float) = {x=u.x+.f; y=u.y+.f; z=u.z+.f}
  let subf (u:vec3) (f:float) = {x=u.x-.f; y=u.y-.f; z=u.z-.f}
  let mulf (u:vec3) (f:float) = {x=u.x*.f; y=u.y*.f; z=u.z*.f}
  let divf (u:vec3) (f:float) = {x=u.x/.f; y=u.y/.f; z=u.z/.f}
  let dot (u:vec3) (v:vec3) = u.x*.v.x +. u.y*.v.y +. u.z*.v.z
  let cross (u:vec3) (v:vec3) =
    let d1 = u.y*.v.z -. u.z*.v.y in
    let d2 = u.x*.v.z -. u.z*.v.x in
    let d3 = u.x*.v.y -. u.y*.v.x in
    create_vec3 d1 (-.d2) d3
  let print_vec (u:vec3) =
    printf "%F %F %F " u.x u.y u.z
  let print_vec_i (u:vec3) =
    printf "%d %d %d " (int_of_float u.x) (int_of_float u.y) (int_of_float u.z)
  let ix (u:vec3) (i:int) =
    match i with
    | 0 -> u.x
    | 1 -> u.y
    | 2 -> u.z
    | _ -> failwith "out of bounds"
  let norm2 (u:vec3) = u.x**2. +. u.y**2. +. u.z**2.
  let norm (u:vec3) =  sqrt (u.x**2. +. u.y**2. +. u.z**2.)
  let normalize (u:vec3) = let n = norm u in {x=u.x/.n; y=u.y/.n; z=u.z/.n}
  let lerp (u:vec3) (t:float) (v:vec3) =
    if t <. 0. then u else
      if t >. 1. then v else
        add (mulf u (1.-.t)) (mulf v t)
end

module Ray = struct
  open Vec3
  type ray = {origin:vec3; direction:vec3}
  let create_ray o d = {origin=o; direction=d}
  let point_at_t (r:ray) (t:float) = add r.origin (mulf r.direction t)
  let print_ray (r:ray) =
    print_vec r.origin; print_vec r.direction
end


module Sphere = struct
  open Vec3
  open Ray
  type sphere = {center:vec3; radius:float}
  let create_sphere (c:vec3) (r:float) = {center=c; radius=r}
  let hit_sphere (s:sphere) (r:ray) =
    let oc = sub r.origin s.center in
    let a = dot r.direction r.direction in
    let b = 2. *. (dot oc r.direction) in
    let c = (dot oc oc) -. (s.radius *. s.radius) in
    let discriminant = b*.b -. 4.*.a*.c in
    if discriminant > 0.
    then ((-.b) -. (sqrt discriminant)) /. (2. *. a)
    else -1.
end


module Main = struct
  open Vec3
  open Ray
  open Sphere

  let nx = 200
  let ny = 100
  let ns = 50
  let llc = create_vec3 (-2.) (-1.) (-1.)
  let horizontal = create_vec3 4. 0. 0.
  let vertical = create_vec3 0. 2. 0.

  let gen_ray i = 
    let u = (float (i % nx)) /. (float nx) in
    let v = (float (i / nx)) /. (float ny) in
    create_ray (create_vec3 0. 0. 0.)
               (sum [llc ; mulf horizontal u; mulf vertical v])
    

  let bg1 = create_vec3 0. 0. 0.
  let bg2 = create_vec3 0. 1. 0.
  let s = create_sphere (create_vec3 0. 0. (-1.)) 0.5
        
  let color r =
    let t = hit_sphere s r in
    if t > 0.
    then
      let n = normalize (sub (point_at_t r t) s.center) in
      mulf (addf n 1.) 0.5
    else
      let unit_direction = normalize r.direction in
      let scaled_y = 0.5 *. (unit_direction.y +. 1.) in
      lerp bg1 scaled_y bg2

  let gen_row i =
    let rec aux j acc =
      match j with
      | (-1) -> acc
      | _ -> aux (j-1) ((gen_ray ((i*nx) + j)) :: acc)
    in aux (nx-1) []

  let gen_grid =
    let rec aux i acc =
      match i with
      | (-1) -> acc
      | _ -> aux (i-1) ((gen_row i) :: acc)
    in aux (ny-1) []

  let rec print_row row =
    match row with
    | [] -> ()
    | h::t -> color h |> (fun v -> mulf v 255.) |> print_vec_i ; printf " "; print_row t

  let rec print_grid grid =
    match grid with
    | [] -> ()
    | h::t -> print_row h; printf "\n"; print_grid t

  let print_header () =
    printf "P3\n%d %d\n255\n" nx ny
    
  let main () =
    let grid = gen_grid in
    print_header ();
    print_grid grid
        
end


let () = Main.main ()
