#!/bin/bash

NAZWA=" "
KATALOG=" "


POLECENIE="0"

until [ "$POLECENIE" == "8" ]
do
    echo "1. Nazwa pliku: $NAZWA"
    echo "2. Katalog: $KATALOG"
    echo "3. Czas ostatniej modyfikacji: $CZAS"
    echo "4. Mniejsze niż: $MNIEJSZE"
    echo "5. Większe niż: $WIEKSZE"
    echo "6. Zawartość: $ZAWARTOSC"    
    echo "7. Szukaj: " 
    echo "8. Koniec: "
    echo " "
    read POLECENIE


    case "$POLECENIE" in
        "1") 
            echo "Podaj nazwe szukanego pliku"
            read NAZWA
            SZUKAJ_NAZWA="-name $NAZWA"
			if [ -z $NAZWA ]
			    then
			    SZUKAJ_NAZWA=""
			fi
			;;
        "2")
            echo "Podaj katalog w którym sie znajduje plik:"
            read KATALOG
            SZUKAJ_KATALOG="${KATALOG}"
			if [ -z $KATALOG ]
                then
                SZUKAJ_KATALOG=""
            fi
			;;
        "3")
            echo "Podaj w ciagu którego plik był ostatnio zmodyfikowany (w dniach): "
            read CZAS
			SZUKAJ_CZAS="-mtime -${CZAS}"
			if [ -z $CZAS ]
                then
                SZUKAJ_CZAS=""
            fi
			;;
		"5")
            echo "Podaj minimalny rozmiar pliku: "
            read WIEKSZE
			SZUKAJ_WIEKSZE="-size +${WIEKSZE}k"
			if [ -z $WIEKSZE ]
                then
                SZUKAJ_WIEKSZE=""
            fi
			;;
		"4")
            echo "Podaj maksymalny rozmiar pliku: "
            read MNIEJSZE
			SZUKAJ_MNIEJSZE="-size -${MNIEJSZE}k"
			if [ -z $MNIEJSZE ]
                then
            SZUKAJ_MNIEJSZE=""
            fi
			;;
        "6")
            echo "Podaj zawartosc której szukasz:"
            read ZAWARTOSC
            SZUKAJ_ZAWARTOSC="-exec grep -l \"$ZAWARTOSC\" {} \;"
			if [ -z "$ZAWARTOSC" ]
                then
                SZUKAJ_ZAWARTOSC=""
            fi
			;;
        "7")
            WYSZUKANIE=$(find $SZUKAJ_KATALOG -type f $SZUKAJ_NAZWA $SZUKAJ_WIEKSZE $SZUKAJ_MNIEJSZE $SZUKAJ_CZAS $SZUKAJ_ZAWARTOSC)
            if [ -z "$WYSZUKANIE" ]
                then
                    echo "Nie ma takiego pliku"
                else
                    echo "Znaleziono plik"
            fi
			;;
        "8") 
            echo " ";;
    esac

done