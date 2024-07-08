# Author           : Olga Rodziewicz ( s198421@student.pg.edu.pl )
# Created On       : 03.05.2024
# Last Modified By : Olga Rodziewicz ( s198421@student.pg.edu.pl )
# Last Modified On : 13.05.2024
# Version          : 1.0
#
# Description      : Skrypt ma wyszukiwać pliki mp3 za pomocą id tagów, (niepełna wersja)
# Opis               
#
# Licensed under GPL (see /usr/share/common-licenses/GPL for more details
# or contact # the Free Software Foundation for a copy)
#!/bin/bash

# Funkcja do wyświetlania komunikatów w oknie dialogowym Zenity
display_message() {
    local message="$1"
    zenity --info --title="Wyniki wyszukiwania" --text="$message"
}

# Funkcja do wyszukiwania plików MP3 według identyfikatorów tagów w określonym folderze
search_mp3_by_tag_ids() {
    tag_ids=$(zenity --entry --title="Wyszukiwanie MP3" --text="Podaj identyfikatory tagów oddzielone przecinkami:")
    if [ $? -eq 1 ]; then
        return 1
    fi

    # Inicjalizacja tablicy przechowującej ścieżki do plików
    file_paths=()
    search_folder="$(pwd)/pliki"

    # Podziel identyfikatory tagów na osobne tagi
    IFS=',' read -ra tags <<< "$tag_ids"

    # Szukaj plików MP3 w określonym folderze na podstawie identyfikatorów tagów
    while IFS= read -r file; do
        matched_tags_count=0
        for tag in "${tags[@]}"; do
            # Sprawdź, czy plik zawiera dany tag
            if exiftool "$file" | grep -q -E "$tag"; then
                ((matched_tags_count++))
            fi
        done

        # Jeśli liczba pasujących tagów jest równa liczbie tagów podanych przez użytkownika, dodaj plik do listy wyników
        if [ $matched_tags_count -eq ${#tags[@]} ]; then
            # Pobierz sformatowaną nazwę pliku (Tytuł - Autor)
            formatted_name=$(exiftool -s -s -s -Title -Artist "$file" | sed 's/^$/Nieznany - Nieznany/')
            index=$(( ${#file_paths[@]} / 2 + 1))
            file_paths+=("$index. $formatted_name" "$file")
        fi
    done < <(find "$search_folder" -type f -name "*.mp3")

    # Jeśli znaleziono pliki MP3, wyświetl listę plików w oknie dialogowym Zenity --list
    if [ ${#file_paths[@]} -ne 0 ]; then
        # Zbuduj listę z indeksem i sformatowanymi nazwami plików
        list=()
        for ((i=0; i<${#file_paths[@]}; i+=2)); do
            index=$((i / 2 + 1))
            list+=("$index" "${file_paths[$i]}")
        done
        selected_file=$(zenity --list --title="Wybierz plik MP3" --column="Index" --column="Plik MP3" --text="Wybierz plik MP3:" --height=400 --width=600 "${list[@]}" --print-column=2)
        if [ -n "$selected_file" ]; then
            display_message "Wybrany plik MP3: $selected_file"
        else
            display_message "Nie wybrano żadnego pliku."
        fi
    else
        display_message "Nie znaleziono plików MP3 zawierających podane identyfikatory tagów."
    fi
}

# Pętla wywołująca funkcję wyszukiwania dopóki użytkownik nie kliknie przycisku "Anuluj"
while true; do
    # Wywołanie funkcji wyszukiwania
    search_mp3_by_tag_ids
    # Sprawdź, czy użytkownik kliknął Anuluj
    if [ $? -eq 1 ]; then
        break
    fi
done