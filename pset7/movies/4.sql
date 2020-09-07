SELECT 
    count(id) 
FROM 
    movies as m, ratings as r
WHERE
    1=1
    AND m.id = r.movie_id
    AND r.rating = 10.0
    