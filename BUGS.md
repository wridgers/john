# Bug list

  - higher AA setting results in a darker image

    This is likely caused by floating point inaccuracies. The solution is to
    use integers to track the anti alias loops and calculate the offets
    independently. 

  - refraction doesn't work correctly

    I think this is cause by the order in which the rays are calculated. The
    solution is to check for refraction first. If the object is 80% transparent
    then 20% of the result should come from diffuse (etc). Reflection is
    calculated independently.

