SELECT DISTINCT
    p.name
FROM
    movies as m,
    stars as s,
    people as p
WHERE
    1=1
    AND m.id = s.movie_id
    AND s.person_id = p.id
    AND not p.name = "Kevin Bacon"
    AND not p.birth = 1958
    AND m.id in ( 
        SELECT
            m.id
        FROM
            movies as m,
            stars as s,
            people as p
        WHERE
            1=1
            AND m.id = s.movie_id
            AND s.person_id = p.id
            AND p.name = "Kevin Bacon"
            AND p.birth = 1958
    )
ORDER BY
    p.name