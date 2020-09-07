SELECT
   m.title
FROM
    movies as m,
    stars as s,
    people as p,
    ratings as r
WHERE
    1=1
    AND m.id = s.movie_id
    AND m.id = r.movie_id
    AND s.person_id = p.id
    AND p.name = "Chadwick Boseman"
ORDER BY
    r.rating DESC
LIMIT 5