# Author           : Olga Rodziewicz ( s198421@student.pg.edu.pl )
# Created On       : 13.05.2024
# Last Modified By : Olga Rodziewicz ( s198421@student.pg.edu.pl )
# Last Modified On : 15.05.2024
# Version          : 1.1
#
# Description      : Skrypt ma wyszukiwać pliki mp3 za pomocą id tagów, wyszukane pliki można usunąć odtworzyć albo dodac do ulubionych.
# Opis               Pliki znajdujące się w ulubionych, można z nich usunąć. Dodatkowo jest opcja odtwarzania playlisty ulubionych
#
# Licensed under GPL (see /usr/share/common-licenses/GPL for more details
# or contact # the Free Software Foundation for a copy)
#!/bin/bash

while getopts hv OPTION; do
    case $OPTION in
    h) echo "Skrypt ma wyszukiwać pliki mp3 za pomocą id tagów, wyszukane pliki można usunąć odtworzyć albo dodac do ulubionych. Pliki znajdujące się w ulubionych, można z nich usunąć. Dodatkowo jest opcja odtwarzania playlisty ulubionych"
        ;;
    v) echo "version 1.1"
        ;;
    *) echo "nie mozesz tak zrobić"
    esac
done

display_message() {
    local message="$1"
    zenity --info --title="Wyniki wyszukiwania" --text="$message"
}

get_user_input() {
    tag_ids=$(zenity --entry --title="Wyszukiwanie MP3" --text="Podaj identyfikatory tagów oddzielone przecinkami:")
    if [ $? -eq 1 ]; then
        return 1
    fi
}

# Funkcja do wyszukiwania plików MP3 w określonym folderze na podstawie identyfikatorów tagów
search_mp3_files() {
    file_paths=()
    search_folder="$(pwd)/pliki"
    IFS=',' read -ra tags <<< "$tag_ids"
    while IFS= read -r file; do
        matched_tags_count=0
        for tag in "${tags[@]}"; do
            if exiftool "$file" | grep -q -E "$tag"; then
                ((matched_tags_count++))
            fi
        done
        if [ $matched_tags_count -eq ${#tags[@]} ]; then
            formatted_name=$(exiftool -s -s -s -Title -Artist "$file" | sed 's/^$/Nieznany - Nieznany/')
            index=$(( ${#file_paths[@]} / 2 + 1))
            file_paths+=("$index. $formatted_name" "$file")
        fi
    done < <(find "$search_folder" -type f -name "*.mp3")
}

# Funkcja do wybierania pliku MP3 z listy i zwracania jego ścieżki
select_file() {
    if [ ${#file_paths[@]} -ne 0 ]; then
        list=()
        for ((i=0; i<${#file_paths[@]}; i+=2)); do
            index=$((i / 2 + 1))
            list+=("$index" "${file_paths[$i]}")
        done
        selected_file_index=$(zenity --list --title="Wybierz plik MP3" --column="Index" --column="Plik MP3" --text="Wybierz plik MP3:" --height=400 --width=600 "${list[@]}")
        if [ -n "$selected_file_index" ]; then
            selected_file_path="${file_paths[((selected_file_index - 1) * 2 + 1)]}"
            echo "$selected_file_path"
        fi
    fi
}

# Funkcja do usuwania wybranego pliku
delete_file() {
    local file="$1"
    confirm=$(zenity --question --title="Potwierdź usunięcie" --text="Czy na pewno chcesz usunąć plik $file?")
    if [ $? -eq 0 ]; then
        rm "$file"
        display_message "Plik $file został usunięty."
    fi
}

# Funkcja do odtwarzania wybranego pliku MP3
play_file() {
    local file="$1"
    mpg123 "$file" # używając mpg123 
}

# Ścieżka do pliku przechowującego listę ulubionych piosenek
favourites_file="ulubione.txt"

add_to_favourites() {
    local file="$1"
    if grep -q "$file" "$favourites_file"; then
        display_message "Ten plik już jest w ulubionych."
    else
        echo "$file" >> "$favourites_file"
        display_message "Dodano do ulubionych."
    fi
}

remove_from_favourites() {
    local file="$1"
    if grep -q "$file" "$favourites_file"; then
        # Tworzymy tymczasowy plik bez wybranej ścieżki
        grep -v "$file" "$favourites_file" > "$favourites_file.tmp" && mv "$favourites_file.tmp" "$favourites_file"
        display_message "Usunięto z ulubionych."
    else
        display_message "Ten plik nie jest na liście ulubionych."
    fi
}

# Funkcja do wyświetlania wyników wyszukiwania i umożliwienia operacji na wybranym pliku
actions_on_files() {
    selected_file=$(select_file)
    if [ -n "$selected_file" ]; then
        operation=$(zenity --list --title="Operacje na pliku" --text="Wybrałeś plik o adresie: $selected_file" --column="Operacja" "Usuń" "Odtwórz" "Dodaj do ulubionych" "Usuń z ulubionych" "Anuluj")
        case $operation in
            "Usuń")
                delete_file "$selected_file"
                ;;
            "Anuluj")
                display_message "Operacja anulowana."
                ;;
            "Odtwórz")
                play_file "$selected_file" 
                ;;
            "Dodaj do ulubionych")
                add_to_favourites "$selected_file" 
                ;; 
            "Usuń z ulubionych")
                remove_from_favourites "$selected_file" 
                ;;   
        esac
    else
        display_message "Nie wybrano żadnego pliku."
    fi
}

# Funkcja do odtwarzania wszystkich ulubionych piosenek
play_all_favourites() {
    if [ -s "$favourites_file" ]; then
        while IFS= read -r file; do
            mpg123 "$file" 
        done < "$favourites_file"
    else
        display_message "Lista ulubionych jest pusta."
    fi
}

# Pętla wywołująca funkcję wyszukiwania dopóki użytkownik nie kliknie przycisku "Anuluj"
while true; do
    action=$(zenity --list --title="Wybierz akcję" --column="Akcja" "Odtwórz ulubione" "Wyszukaj plik MP3" --height=200)
    case $action in
        "Odtwórz ulubione")
            play_all_favourites
            ;;
        "Wyszukaj plik MP3")
            get_user_input || break
            search_mp3_files
            actions_on_files
            ;;
        *)
            display_message "Anulowano."
            exit
            ;;
    esac
done
