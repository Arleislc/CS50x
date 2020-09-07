SELECT DISTINCT
   name
FROM
    movies as m,
    stars as s,
    people as p
WHERE
    1=1
    AND m.id = s.movie_id
    AND s.person_id = p.id
    AND m.year = 2004
ORDER BY
    p.birth