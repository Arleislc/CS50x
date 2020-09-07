
SELECT
    m.title
FROM
    movies as m,
    stars as s,
    people as p
WHERE
    1=1
    AND m.id = s.movie_id
    AND s.person_id = p.id
    AND p.name = "Johnny Depp"
    AND m.title in (
        SELECT
            m.title
        FROM
            movies as m,
            stars as s,
            people as p
        WHERE
            1=1
            AND m.id = s.movie_id
            AND s.person_id = p.id
            AND p.name = "Helena Bonham Carter"
    )
