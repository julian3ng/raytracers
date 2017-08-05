open Core
   
module Vec3 = struct
  type vec3 = {x:float; y:float; z:float}
  let create (x:float) (y:float) (z:float) = {x=x; y=y; z=z}
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
    create d1 (-.d2) d3
  let print (u:vec3) =
    printf "%F %F %F" u.x u.y u.z
  let ix (u:vec3) (i:int) =
    match i with
    | 0 -> u.x
    | 1 -> u.y
    | 2 -> u.z
    | _ -> failwith "out of bounds"
end
