--3. Gyakorlat
--1.  Kik azok a dolgozók, akiknek a fizetése nagyobb, mint 2800?
SELECT DNEV, DKOD FROM DOLGOZO WHERE FIZETES > 2800;

--2.  Kik azok a dolgozók, akik a 10-es vagy a 20-as osztályon dolgoznak?
SELECT DISTINCT DNEV, DKOD FROM DOLGOZO WHERE OAZON = 10 OR OAZON = 20;

--3.  Kik azok, akiknek a jutaléka nagyobb, mint 600?
SELECT DNEV, DKOD FROM DOLGOZO WHERE JUTALEK > 600;

--4.  Kik azok, akiknek a jutaléka nem nagyobb, mint 600?
SELECT DNEV, DKOD FROM DOLGOZO WHERE JUTALEK <= 600;

--5.  Kik azok a dolgozók, akiknek a jutaléka ismeretlen (nincs kitöltve, vagyis NULL)?
SELECT DNEV, DKOD FROM DOLGOZO WHERE JUTALEK IS NULL;

--6.  Adjuk meg a dolgozók között előforduló foglalkozások neveit.
SELECT DISTINCT FOGLALKOZAS FROM DOLGOZO;

--7.  Adjuk meg azoknak a nevét és kétszeres fizetését, akik a 10-es osztályon dolgoznak.
SELECT DNEV, FIZETES * 2 FROM DOLGOZO WHERE OAZON = 10;

--8.  Kik azok a dolgozók, akik 1982.01.01 után léptek be a céghez?
SELECT DNEV, BELEPES FROM DOLGOZO WHERE BELEPES >= TO_DATE('1982.01.01','yyyy.mm.dd');

--9.  Kik azok, akiknek nincs főnöke?
SELECT DNEV FROM  DOLGOZO WHERE FONOKE IS NULL;

--10. Kik azok a dolgozók, akiknek a nevében van 'A' betű?
SELECT DNEV FROM DOLGOZO WHERE DNEV LIKE '%A%';

--11. Kik azok a dolgozók, akiknek a nevében van két 'L' betű?
SELECT DNEV FROM DOLGOZO WHERE DNEV LIKE '%L%L%';

--12. Kik azok a dolgozók, akiknek a fizetése 2000 és 3000 között van?
SELECT DNEV, FIZETES FROM DOLGOZO WHERE FIZETES < 3000 AND FIZETES > 2000;

--13. Adjuk meg a dolgozók adatait fizetés szerint növekvő sorrendben.
SELECT * FROM DOLGOZO ORDER BY FIZETES ASC;

--14. Adjuk meg a dolgozók adatait fizetés szerint csökkenő, azon belül név szerinti sorrendben.
SELECT * FROM DOLGOZO ORDER BY FIZETES DESC, DNEV ASC;

--15. Kik azok a dolgozók, akiknek a főnöke KING? (egyelőre leolvasva a képernyőről)
SELECT * FROM DOLGOZO D1, DOLGOZO D2 WHERE D1.FONOKE = D2.DKOD AND D2.DNEV = 'KING';

-- Kötelező feladat:
DROP TABLE GYAK3;
CREATE TABLE GYAK3 AS SELECT D1.DNEV Beosztott, D2.dnev Kozv_Fonoke
FROM DOLGOZO D1, DOLGOZO D2
WHERE D1.FONOKE = D2.DKOD
AND LENGTH(D1.dnev) = LENGTH(D2.DNEV);

--Fizetési kategóriás feladatok
SELECT DNEV, KATEGORIA FROM DOLGOZO, FIZ_KATEGORIA WHERE FIZETES BETWEEN ALSO AND FELSO;