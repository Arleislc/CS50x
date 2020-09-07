SELECT
   name
FROM
    movies as m,
    directors as d,
    people as p,
    ratings as r
WHERE
    1=1
    AND m.id = d.movie_id
    AND m.id = r.movie_id
    AND d.person_id = p.id
    AND r.rating >= 9.0