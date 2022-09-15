-- 1.  Melyek azok a gyümölcsök, amelyeket Micimackó szeret?
-- 2.  Melyek azok a gyümölcsök, amelyeket Micimackó nem szeret? (de valaki más igen)
-- 3.  Kik szeretik az almát?
-- 4.  Kik nem szeretik a körtét? (de valami mást igen)
-- 5.  Kik szeretik vagy a epret vagy a körtét?
-- 6.  Kik szeretik az almát is és a körtét is?
-- 7.  Kik azok, akik szeretik az almát, de nem szeretik a körtét? eddig volt korábban, lásd feladat1.txt
-- 8.  Kik szeretnek legalább kétféle gyümölcsöt?
-- 9.  Kik szeretnek legalább háromféle gyümölcsöt?
-- 10. Kik szeretnek legfeljebb kétféle gyümölcsöt?
-- 11. Kik szeretnek pontosan kétféle gyümölcsöt?

--1. Feladat
SELECT GYUMOLCS
FROM SZERET
WHERE NEV='Micimackó';

--2. Feladat
SELECT GYUMOLCS FROM SZERET MINUS
SELECT DISTINCT GYUMOLCS -- Distinct - csak egyszer jeleníti meg a lekérdeztünk (pl.: nem lesz alma alma alma csak annyi hogy alma)
FROM SZERET WHERE NEV='Micimackó';

--3. Feladat
SELECT NEV FROM SZERET WHERE GYUMOLCS='alma';

--4. Feladat
SELECT DISTINCT NEV FROM SZERET MINUS SELECT NEV FROM SZERET WHERE GYUMOLCS='körte';

--5. Feladat -- Megengedő vagy = UNION / OR;
SELECT DISTINCT NEV
FROM SZERET
WHERE GYUMOLCS='alma' OR GYUMOLCS='eper';

--6. Feladat
SELECT DISTINCT NEV
FROM SZERET
WHERE GYUMOLCS='alma'
INTERSECT
SELECT DISTINCT NEV
FROM SZERET
WHERE GYUMOLCS='körte';

--7. Feladat
SELECT NEV
FROM SZERET
WHERE GYUMOLCS='alma'
MINUS
SELECT NEV
FROM SZERET
WHERE GYUMOLCS='eper';

--8. Feladat
SELECT DISTINCT s1.NEV
FROM SZERET s1, SZERET s2
WHERE s1.NEV = s2.NEV
AND s1.GYUMOLCS != s2.GYUMOLCS;

--9. Feladat
SELECT DISTINCT s1.NEV
FROM SZERET s1, SZERET s2, SZERET s3
WHERE s1.NEV = s2.NEV AND s1.NEV = s3.NEV AND s2.NEV = s3.NEV
AND s1.GYUMOLCS != s2.GYUMOLCS AND s1.GYUMOLCS != s3.GYUMOLCS AND s2.GYUMOLCS != s3.GYUMOLCS;

--10. Feladat
SELECT DISTINCT NEV
FROM SZERET
MINUS
SELECT DISTINCT s1.NEV
FROM SZERET s1, SZERET s2, SZERET s3
WHERE s1.NEV = s2.NEV AND s1.NEV = s3.NEV AND s2.NEV = s3.NEV
AND s1.GYUMOLCS != s2.GYUMOLCS AND s1.GYUMOLCS != s3.GYUMOLCS AND s2.GYUMOLCS != s3.GYUMOLCS;

--11. Feladat
SELECT DISTINCT NEV
FROM SZERET
MINUS
SELECT DISTINCT s1.NEV
FROM SZERET s1, SZERET s2, SZERET s3
WHERE s1.NEV = s2.NEV AND s1.NEV = s3.NEV AND s2.NEV = s3.NEV
AND s1.GYUMOLCS != s2.GYUMOLCS AND s1.GYUMOLCS != s3.GYUMOLCS AND s2.GYUMOLCS != s3.GYUMOLCS
MINUS
(SELECT DISTINCT NEV
FROM SZERET
MINUS
SELECT DISTINCT s1.NEV
FROM SZERET s1, SZERET s2, SZERET s3
WHERE s1.NEV = s2.NEV AND s1.NEV = s3.NEV
AND s1.GYUMOLCS = s2.GYUMOLCS AND s3.GYUMOLCS != s1.GYUMOLCS);

-- Házi
SELECT DISTINCT NEV
FROM SZERET
WHERE GYUMOLCS='alma'
INTERSECT
SELECT DISTINCT NEV
FROM SZERET
WHERE GYUMOLCS='körte';


