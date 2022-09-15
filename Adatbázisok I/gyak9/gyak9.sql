----------------------9.Gyakoralt
--1.Feladat
/* SELECT ... INTO v1
Írjunk meg egy függvényt, amelyik visszaadja egy adott fizetési kategóriába tartozó
dolgozók átlagfizetését.*/

CREATE OR REPLACE FUNCTION kat_atlag(N INTEGER) RETURN NUMBER IS
BEGIN
    DECLARE
    ASD NUMBER;
    BEGIN
        SELECT AVG(FIZETES) INTO ASD FROM DOLGOZO,FIZ_KATEGORIA WHERE KATEGORIA = N;
        RETURN ASD;
    END;
END;

SELECT kat_atlag(2) FROM dual;

--2.Feladat
/* SELECT ... INTO v1, v2
Írjunk meg egy procedúrát, amelyik kiírja azon dolgozók számát és átlagfizetését,
akiknek a belépési dátuma a paraméterül megadott nevű napon (pl. 'Hétfő') volt.*/

CREATE OR REPLACE FUNCTION nap_nev(p_kar VARCHAR2) RETURN VARCHAR2 IS
BEGIN
    DECLARE
        l_date date;
    BEGIN
        l_date := to_date( p_kar, 'YYYY/MM/DD' );
        RETURN TO_CHAR(l_date, 'Day');
    EXCEPTION
        WHEN others THEN
            DBMS_OUTPUT.ENABLE;
            DBMS_OUTPUT.PUT_LINE('Nem megfelelő formatum.');
        RETURN null;
    END;
END;

CREATE OR REPLACE PROCEDURE nap_atl(d varchar2) IS
BEGIN
    DECLARE
        CURSOR CURS1 (OA NUMBER) IS SELECT distinct FIZETES, nap_nev(BELEPES) as NAP FROM DOLGOZO;
        REC CURS1%ROWTYPE;
        counter number;
        summation number;
    BEGIN
        counter := 0;
        summation := 0;
        OPEN CURS1(1);
        LOOP
            FETCH CURS1 INTO REC;
            EXIT WHEN CURS1%NOTFOUND;
            if(regexp_replace(rec.NAP, '[[:space:]]*','') = d) then
                counter := counter + 1;

                summation := summation + rec.FIZETES;
            end if;
        END LOOP;
        CLOSE CURS1;
        DBMS_OUTPUT.PUT_LINE('Atlag: ' || summation/counter || ' Hanyan leptek be: ' || counter);
    END;
END;

call nap_atl('Csütörtök');

--3.Feladat
/* Insert, Delete, Update
Írjunk meg egy procedúrát, amelyik megnöveli azoknak a dolgozóknak a fizetését, akiknek a
fizetési kategóriája ugyanaz, mint a procedúra paramétere. A növelés mértéke a dolgozó
osztályában előforduló legkisebb fizetés legyen.
A procedúra a módosítás után írja ki a módosított (új) fizetések átlagát két tizedesjegyre kerekítve.
*/

SELECT FIZETES, KATEGORIA, OAZON FROM DOLGOZO natural join FIZ_KATEGORIA where fizetes between also and felso;

CREATE OR REPLACE PROCEDURE kat_novel(p_kategoria NUMBER) IS
BEGIN
    DECLARE
        CURSOR CURS1 (OA NUMBER) IS SELECT FIZETES, KATEGORIA, OAZON FROM DOLGOZO natural join FIZ_KATEGORIA where fizetes between also and felso;
        REC CURS1%ROWTYPE;
        CURSOR CURS2 (OA NUMBER) IS SELECT FIZETES, KATEGORIA, OAZON FROM DOLGOZO natural join FIZ_KATEGORIA where fizetes between also and felso;
        REC2 CURS2%ROWTYPE;
        minimumfizetes number;
    BEGIN
        OPEN CURS1(1);
        LOOP
            FETCH CURS1 INTO REC;
            EXIT WHEN CURS1%NOTFOUND;
            OPEN CURS2(1);
            LOOP
                FETCH CURS2 INTO REC2;
                EXIT WHEN CURS2%NOTFOUND;
            END LOOP;
            CLOSE CURS2;
            UPDATE DOLGOZO_2 SET fizetes = fizetes+minimumfizetes WHERE rec.KATEGORIA = p_kategoria;
            COMMIT;
        END LOOP;
        CLOSE CURS1;
    END;
END;

BEGIN
    kat_novel(2);
end;

--DROP TABLE DOLGOZO_2;
--CREATE TABLE DOLGOZO_2 AS SELECT * FROM DOLGOZO;