--1. feladat:
--Melyek azok a (név, név) párok, akiknek legalább egy gyümölcsben eltér az ízlésük,
--azaz az egyik szereti ezt a gyümölcsöt, a másik meg nem (NEV, NEV)?

CREATE VIEW NEVEK(O1, O2, O3, O4) AS SELECT DISTINCT SZ1.NEV AS NEV, SZ2.GYUMOLCS, SZ2.NEV AS NEV, SZ1.GYUMOLCS
FROM SZERET SZ1, SZERET SZ2
MINUS
SELECT DISTINCT SZ1.NEV AS NEV, SZ1.GYUMOLCS, SZ2.NEV AS NEV, SZ2.GYUMOLCS
FROM SZERET SZ1, SZERET SZ2;
SELECT DISTINCT O1 AS NEV, O3 AS NEV FROM NEVEK;

-- RELÁCIÓS ALGEBRA:
-- π$1$3( (ρ NEV←SZ1.NEV, NEV←SZ2.NEV π SZ1.NEV, SZ2.GYUMOLCS, SZ2.NEV, SZ1.GYUMOLCS ( ρ SZ1 SZERET ⨯ ρ SZ2 SZERET )) -
--        (ρ NEV←SZ1.NEV, NEV←SZ2.NEV π SZ1.NEV, SZ1.GYUMOLCS, SZ2.NEV, SZ2.GYUMOLCS ( ρ SZ1 SZERET ⨯ ρ SZ2 SZERET )) )

--2. feladat:
--Melyek azok a gyümölcsök, amelyeket pontosan azok szeretik, akik a 'körte'-t is szeretik (GYUMOLCS)?

SELECT DISTINCT SZ2.GYUMOLCS
FROM SZERET SZ1, SZERET SZ2
WHERE SZ1.GYUMOLCS = 'körte' AND SZ1.NEV = SZ2.NEV;

-- RELÁCIÓS ALGEBRA: π SZ2.gyumolcs σ SZ1.gyumolcs = 'körte' and SZ1.nev = SZ2.nev ( ρ SZ1 Szeret ⨯ ρ SZ2 Szeret )

--3. feladatú:
--Adjuk meg azoknak a dolgozóknak a kódját és nevét, akik többet keresnek a közvetlen főnöküknél,
--és legalább egy beosztottjuknál is (DKOD, DNEV).

SELECT D1.DKOD, D1.DNEV
FROM DOLGOZO D1, DOLGOZO D2, DOLGOZO D3
WHERE D1.FONOKE = D2.DKOD
AND D2.FONOKE = D3.DKOD
AND D1.FIZETES < D2.FIZETES
AND D3.FIZETES < D2.FIZETES;

-- RELÁCIÓS ALGEBRA: π d1.dkod, d1.dnev σ d1.fonoke = d2.dkod and d2.fonoke = d3.dkod and d1.fizetes < d2.fizetes and d3.fizetes < d2.fizetes ( ( ρ d1 Dolgozo ⨯ ρ d2 Dolgozo ) ⨯ ρ d3 Dolgozo )

--4. feladat:
--Melyek azok a gyümölcsök, amelyeket legalább azok szeretik, akik az alma-t szeretik (GYUMOLCS)

SELECT DISTINCT GYUMOLCS FROM SZERET WHERE NEV IN
(SELECT NEV FROM SZERET WHERE GYUMOLCS = 'alma');

--5. feladat:
--Adjuk meg azokat a (név, közvetlen_főnök) párokat,
--ahol a két ember foglalkozásának a neve ugyanannyi betűből áll (DNEV, DNEV).

SELECT D1.DNEV AS Név, D2.DNEV AS Közvetlen_főnök FROM DOLGOZO D1, DOLGOZO D2
WHERE D1.FONOKE = D2.DKOD AND LENGTH(D1.DNEV) = LENGTH(D2.DNEV);

--6. feladat:
--Adjuk meg azokat a (DNEV, DNEV), azaz (dolgozó név, nagyfőnök név) párokat, ahol a "nagyfőnök nevű" a "dolgozó nevű"
--közvetlen főnökének a közvetlen főnöke, és mindkettőjük nevében szerepel legalább két 'A' betű.

SELECT D1.DNEV AS Dolgozó_név, D3.DNEV AS Nagyfőnök_nev FROM DOLGOZO D1, DOLGOZO D2, DOLGOZO D3
WHERE D1.FONOKE = D2.DKOD AND D2.FONOKE = D3.DKOD AND D1.DNEV LIKE '%A%A%' AND D3.DNEV LIKE '%A%A%';

--7. feladat:
--Adjuk meg azon piros színű cikkek kódját és nevét, amelyeket sehova nem szállítanak. [ckod, cnev]

SELECT DISTINCT CKOD, CNEV FROM CIKK
WHERE CKOD NOT IN
(SELECT DISTINCT CKOD FROM SZALLIT) AND SZIN = 'piros';

--8. feladat:
--Melyik cikket szállítják a legtöbb projekthez ? [ckod, cnev]

WITH MEGSZAMOLT(CKOD, DB) AS (
        SELECT CKOD, COUNT(CKOD) FROM SZALLIT GROUP BY CKOD ORDER BY CKOD
    ),
    MAX_DARAB(DB) AS (
        SELECT MAX(DB) FROM MEGSZAMOLT
    )
SELECT CIKK.CKOD, CIKK.CNEV FROM MAX_DARAB, MEGSZAMOLT, CIKK
WHERE MEGSZAMOLT.DB = MAX_DARAB.DB AND MEGSZAMOLT.CKOD = CIKK.CKOD;