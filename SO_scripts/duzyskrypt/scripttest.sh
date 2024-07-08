#!/usr/bin/bash

#Author : Jakub Drejka
#Index: 198083
#Description: mp3 file browser and filter, which allows the user to play selected songs
#Version: 1.0.0-beta
#Licensed under BigosMusic Poland

while getopts "hv" opt; do          #ogarniecie parametrow wejscia w skrypt
    case $opt in
        h)
            echo "Prosty skrypt filtrujący i umozliwiajcy puszczanie piosenek"
            exit 0
            ;;
        v)
            echo "version 1.0.0-beta"
            exit 0
            ;;
    esac
done


search_for_files() {            #wyszukiwanie
    zenity --info --text="Wyszukiwanie plików mp3" --width=200 --height=100
    mp3_files=$(find $directory -type f -iname "*.mp3")     #baza plikow mp3 z podanego folderu
    found=()                #bazy tagow do filtrowania
    tags=()
    values=()
    if [ -n "$title" ]; then            #przypisanie wartosci wpisanych
        tags+=("Title")
        values+=("$title")
    fi
    if [ -n "$artist" ]; then
        tags+=("Artist")
        values+=("$artist")
    fi
    if [ -n "$genre" ]; then
        tags+=("Genre")
        values+=("$genre")
    fi
    if [ -n "$album" ]; then
        tags+=("Album")
        values+=("$album")
    fi
    if [ -n "$publisher" ]; then
        tags+=("Publisher")
        values+=("$publisher")
    fi
    if [ -n "$year" ]; then
        tags+=("Year")
        values+=("$year")
    fi
    found=()
    for file in $mp3_files; do      #iteracja po parametrach filtracji
        flag=true
        for ((i = 0; i < ${#tags[@]}; i++)); do
            tag="${tags[$i]}"
            value="${values[$i]}"

            if [ -n "$value" ]; then
                tag_value=$(exiftool -ignoreMinorErrors -s -s -s -"$tag" "$file" 2>/dev/null) #wyszukanie taga
                if [ "$tag_value" != "$value" ]; then                                         #porownanie go z wartoscia podana przez uzytkownika
                    flag=false
                    break
                fi
            fi
        done
        if $flag; then
            found+=("$file")  #dopisanie pliku spelniajacego kryteria
        fi
    done
    if [ ${#found[@]} -eq 0 ]; then
        zenity --info --text="Nie znaleziono żadnych plików" --title="Wyniki wyszukiwania"
    else
        selected_file=$(zenity --list --title="Wyniki wyszukiwania" --text="Znalezione pliki:" --column="Pliki" "${found[@]}")                  #lista znalezionych plikow, do wyboru ktory odtworzayc
        if [ -n "$selected_file" ]; then
            play_song "$selected_file"
        fi
    fi
}

play_song() {           #logia odtworzenia utworu
    local file=$1
    
    if command -v totem &> /dev/null; then      #czysci output
        nohup totem "$file" > /dev/null 2>&1 &          #& dzialanie w tle
    else
        zenity --error --text="Nie znaleziono domyślnego odtwarzacza (totem)." --width=300 --height=100
    fi
}

while true; do                  #przyjmowanie parametrow oraz konczenie dzialania
    Menu=("1. Tytuł:$title" "2. Artysta:$artist" "3. Gatunek:$genre" "4. Album:$album" "5. Wydawnictwo:$publisher" "6. Rok wydania:$year" "7. Katalog:$directory" "8. Szukaj" "9. Koniec")
    choice=$(zenity --list --title="MP3 wyszukiwacz" --text="Wybierz opcje" --column=Menu "${Menu[@]}" --height=300)
    case $choice in
        "1. Tytuł:$title")
            title=$(zenity --entry --text="Podaj tytuł:" --title="Tytuł" --width=300 --height=100)
            ;;
        "2. Artysta:$artist")
            artist=$(zenity --entry --text="Podaj artystę:" --title="Artysta" --width=300 --height=100)
            ;;
        "3. Gatunek:$genre")
            genre=$(zenity --entry --text="Podaj gatunek:" --title="Gatunek" --width=300 --height=100)
            ;;
        "4. Album:$album")
            album=$(zenity --entry --text="Podaj album:" --title="Album" --width=300 --height=100)
            ;;
        "5. Wydawnictwo:$publisher")
            publisher=$(zenity --entry --text="Podaj wydawnictwo:" --title="Wydawnictwo" --width=300 --height=100)
            ;;
        "6. Rok wydania:$year")
            year=$(zenity --entry --text="Podaj rok wydania:" --title="Rok wydania" --width=300 --height=100)
            ;;
        "7. Katalog:$directory")
            directory=$(zenity --file-selection --directory --title="Wybierz katalog" --width=400 --height=300)
            ;;
        "8. Szukaj")
            search_for_files
            ;;
        "9. Koniec")
            exit 0
            ;;
        *)
            zenity --error --text="Nieprawidlowy wybor." --width=200 --height=100
            ;;
    esac
done

