SELECT
    AVG(rating)
FROM
    movies as m, ratings as r
WHERE
    1=1
    AND m.id = r.movie_id
    AND m.year = 2012