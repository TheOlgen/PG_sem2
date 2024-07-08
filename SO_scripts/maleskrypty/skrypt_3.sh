zenity --info --title "skrypt 3" --text "w tym programie sprawdzisz czy dany plik istnieje"
POLECENIE="0"

until [ "$POLECENIE" == "8" ]
do
    menu=("1. Nazwa pliku: $NAZWA" "2. Katalog: $KATALOG" "3. Czas ostatniej modyfikacji: $CZAS" "4. Mniejsze niż: $MNIEJSZE" "5. Większe niż: $WIEKSZE" "6. Zawartość: $ZAWARTOSC" "7. Szukaj: " "8. Koniec: ")
    odp=`zenity --list --column=Menu "${menu[@]}" --height 400 --title "skrypt 3"`

    case "$odp" in
        "1. Nazwa pliku: $NAZWA") 
            NAZWA=`zenity --entry --title "skrypt 3" --text "Podaj nazwe szukanego pliku"`
            SZUKAJ_NAZWA="-name $NAZWA"
			if [ -z $NAZWA ]
			    then
			    SZUKAJ_NAZWA=""
			fi
			;;
        "2. Katalog: $KATALOG")
            KATALOG=`zenity --entry --title "skrypt 3" --text "Podaj nazwe katalogu w którym szukasz"`
            SZUKAJ_KATALOG="${KATALOG}"
			if [ -z $KATALOG ]
                then
                SZUKAJ_KATALOG=""
            fi
			;;
        "3. Czas ostatniej modyfikacji: $CZAS")
            CZAS=$(zenity --scale --title "skrypt 3" --text "Podaj czas w jakim ten plik mógłbyć edytowany" --min-value 1 --max-value 60 --value 10)
			SZUKAJ_CZAS="-mtime -${CZAS}"
			if [ -z $CZAS ]
                then
                SZUKAJ_CZAS=""
            fi
			;;
		"5. Większe niż: $WIEKSZE")
            WIEKSZE=$(zenity --scale --title "skrypt 3" --text "komunikat" --min-value 1 --max-value 60 --value 10)
			SZUKAJ_WIEKSZE="-size +${WIEKSZE}k"
			if [ -z $WIEKSZE ]
                then
                SZUKAJ_WIEKSZE=""
            fi
			;;
		"4. Mniejsze niż: $MNIEJSZE")
            MNIEJSZE=$(zenity --scale --title "skrypt 3" --text "komunikat" --min-value 1 --max-value 60 --value 10)
			SZUKAJ_MNIEJSZE="-size -${MNIEJSZE}k"
			if [ -z $MNIEJSZE ]
                then
            SZUKAJ_MNIEJSZE=""
            fi
			;;
        "6. Zawartość: $ZAWARTOSC")
            ZAWARTOSC=`zenity --entry --title "skrypt 3" --text "komunikat"`
            SZUKAJ_ZAWARTOSC="-exec grep -l \"$ZAWARTOSC\" {} \;"
			if [ -z "$ZAWARTOSC" ]
                then
                SZUKAJ_ZAWARTOSC=""
            fi
			;;
        "7. Szukaj: ")
            WYSZUKANIE=$(find $SZUKAJ_KATALOG -type f $SZUKAJ_NAZWA $SZUKAJ_WIEKSZE $SZUKAJ_MNIEJSZE $SZUKAJ_CZAS $SZUKAJ_ZAWARTOSC)
            if [ -z "$WYSZUKANIE" ]
                then
                    zenity --info --title "skrypt 3" --text "Nie ma takiego pliku"
                else
                    zenity --info --title "skrypt 3" --text ""Znaleziono plik""
            fi
			;;
        "8. Koniec: ") 
            POLECENIE="8"
            echo " ";;
    esac
done
