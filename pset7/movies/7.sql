SELECT
    title,
    rating
FROM 
    movies as m,
    ratings as r
WHERE
    1=1
    AND m.id = r.movie_id
    AND year = 2010
ORDER BY
    rating DESC,
    title ASC
    