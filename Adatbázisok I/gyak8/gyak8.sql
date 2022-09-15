--1. Feladat:
--Írjunk meg egy függvényt, amelyik eldönti egy számról, hogy prím-e. igen/nem -> 1/0
CREATE OR REPLACE FUNCTION prim(n IN INTEGER) RETURN NUMBER IS
BEGIN
    DECLARE
        i NUMBER;
        is_prime NUMBER;
    BEGIN
        i := 2;
        is_prime := 1;
        FOR i IN 2..n/2 LOOP
            IF mod(n, i) = 0 THEN
                is_prime := 0;
                EXIT;
            END IF;
        END LOOP;
        IF is_prime = 1 THEN
            RETURN 1; -- true
        ELSE
            RETURN 0; -- false
        END IF;
    END;
END;

SELECT DKOD, DNEV FROM DOLGOZO WHERE prim(DKOD) = 1;

--2. Feladat:
--Írjunk meg egy procedúrát, amelyik kiírja az n-edik Fibonacchi számot
--fib_1 = 0, fib_2 = 1, fib_3 = 1, fib_4 = 2 ... fib_i = a megelőző kettő összege
CREATE OR REPLACE PROCEDURE fib(N INTEGER) IS
BEGIN
    DECLARE
        T1 NUMBER;
        T2 NUMBER;
        NEXT_NUMBER NUMBER;
    BEGIN
        T1 := 0;
        T2 := 1;
        NEXT_NUMBER := T1 + T2;
        dbms_output.put_line('Fibonacchi sorozat ' || N || '-dik számáig: ');
        IF N = 1 THEN
            dbms_output.put_line( '1.: ' || T1);
        ELSIF N = 2 THEN
            dbms_output.put_line('1.: ' || T1);
            dbms_output.put_line('2.: ' || T2);
        ELSE
            dbms_output.put_line('1.: ' || T1);
            dbms_output.put_line('2.: ' || T2);
            FOR I IN 3..N LOOP
                dbms_output.put_line(I || '.: ' || NEXT_NUMBER);
                T1 := T2;
                T2 := NEXT_NUMBER;
                NEXT_NUMBER := T1 + T2;
            END LOOP;
        END IF;
    END;
END;

BEGIN
    fib(10);
END;

-- 3. Feladat:
--Írjunk meg egy függvényt, amelyik visszaadja két szám legnagyobb közös osztóját
CREATE OR REPLACE FUNCTION lnko(P1 INTEGER, P2 INTEGER) RETURN NUMBER IS
BEGIN
    DECLARE
        GCD NUMBER;
        I NUMBER;
    BEGIN
        I := 1;
        WHILE I <= P1 AND I <= P2 LOOP
            IF MOD(P1, I) = 0 AND MOD(P2, I) = 0 THEN
                GCD := I;
            END IF;
            I := I + 1;
        END LOOP;
        RETURN GCD;
    END;
END;
SELECT lnko(3570,7293) FROM DUAL;

--4. Feladat:
--Írjunk meg egy függvényt, amelyik visszaadja n faktoriálisát
CREATE OR REPLACE FUNCTION faktor(N INTEGER) RETURN INTEGER IS
BEGIN
    DECLARE
        FACTORIAL NUMBER;
    BEGIN
        FACTORIAL := 1;
        FOR I IN 1..N LOOP
            FACTORIAL := I * FACTORIAL;
        END LOOP;
        RETURN FACTORIAL;
    END;
END;
SELECT faktor(33) FROM DUAL;

--5. Feladat:
--Írjunk meg egy függvényt, amelyik megadja, hogy hányszor fordul elő egy
--karakterláncban -> p1 egy másik részkarakterlánc -> p2
CREATE OR REPLACE FUNCTION hanyszor(P1 VARCHAR2, P2 VARCHAR2) RETURN INTEGER IS
BEGIN
    DECLARE
        STR VARCHAR2(200);
        J NUMBER;
        COUNTER NUMBER;
        TYPE VARCHAR_ARRAY IS VARRAY(20) OF VARCHAR2(20);
        STR_ARRAY VARCHAR_ARRAY := VARCHAR_ARRAY();
    BEGIN
        J := 1;
        STR := '';
        FOR I IN 1..LENGTH(P1) LOOP
            IF SUBSTR( P1, I, 1 ) != ' ' THEN
                STR := STR || SUBSTR( P1, I, 1 );
            ELSE
                STR_ARRAY.extend();
                STR_ARRAY(J) := STR;
                J := J + 1;
                STR := '';
            END IF;
        END LOOP;
        COUNTER := 0;
        FOR I IN 1..STR_ARRAY.COUNT LOOP
            IF STR_ARRAY(I) = P2 THEN
                COUNTER := COUNTER + 1;
            END IF;
        END LOOP;
        RETURN COUNTER;
    END;
END;

SELECT hanyszor('ab c ab ab de ab fg', 'ab') FROM dual;

--6. Feladat:
--Írjunk meg egy függvényt, amelyik visszaadja a paraméterként szereplő '+'-szal elválasztott számok összegét.
CREATE OR REPLACE FUNCTION osszeg(P_CHAR VARCHAR2) RETURN NUMBER IS
BEGIN
    DECLARE
        STR VARCHAR2(10);
        RET NUMBER;
    BEGIN
        STR := '';
        RET := 0;
        FOR I IN 1..LENGTH(P_CHAR) LOOP
            IF SUBSTR( P_CHAR, I, 1 ) != '+' THEN
                STR := STR || SUBSTR( P_CHAR, I, 1 );
            ELSE
                RET := RET + TO_NUMBER(STR);
                STR := '';
            END IF;
        END LOOP;
        RET := RET + TO_NUMBER(STR);
        RETURN RET;
    END;
END;

SELECT osszeg('2+3+4+-5') FROM dual;