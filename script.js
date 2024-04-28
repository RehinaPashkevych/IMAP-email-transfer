
const languageData = {

    en: {
        "title": "IMAP Email Transfer Help",
        "header": "IMAP Email Transfer Help Documentation",
        "overviewTitle": "Overview",
        "overviewContent": "This document provides a basic understanding of how IMAP requests are used within this application to transfer emails between servers.",
        "whatIsImapTitle": "What is IMAP?",
        "whatIsImapContent": "IMAP (Internet Message Access Protocol) allows users to access and manipulate their email on a remote server through a local client. Unlike POP, IMAP syncs with the server, allowing multiple clients to see the same folder state.",
        "usingImapTitle": "Using IMAP in This Application",
        "usingImapIntro": "Follow these detailed steps to use IMAP effectively in this application:",
        "step1": "Provide URL, Email, and Password: Start by entering your server's URL, email address, and password. Test your connection by listing mailboxes to ensure you're connected correctly.",
        "step2": "View Mailbox List: Click 'List of Mailboxes' to see a list of all folders/mailboxes. Each mailbox is displayed with its attributes.",
        "mailboxExample1": "* LIST (\\HasNoChildren \\Drafts) \"/\" \"Drafts\": Indicates a Drafts folder with no child folders.",
        "mailboxExample2": "* LIST (\\HasNoChildren) \"/\" \"INBOX\": Shows the INBOX which holds all incoming emails.",
        "mailboxExample3": "* LIST (\\NoInferiors \\Junk) \"/\" \"Junk\": A Junk folder that cannot contain sub-folders.",
        "step3": "Select a Mailbox: Typically, this is 'INBOX' for incoming mail.",
        "step4": "Use IMAP Commands: Implement commands to manage your emails. Examples include:",
        "imapExample1": "UID SEARCH SINCE 15-Apr-2024: Searches for all emails received since April 15, 2024. ",
        "imapExample2": "UID FETCH <UID> (RFC822) or FETCH <UID> BODY[TEXT]: Fetches the entire email corresponding to a specific UID. ",
        "imapExample3": "UID SEARCH ALL: Finds all emails in the mailbox. ",
        "imapExample4": "SEARCH FROM \"example@example.com\": Search for messages from a specific sender. ",
        "step5": "Save Emails: To save an email, ensure you have the correct mailbox and UID, then use the 'Save email' function.",
        "step6": "Transfer Emails: After saving, provide the destination server's URL, email address, and password, along with the mailbox to transfer emails to. Use the 'transfer' button to initiate the process. Check by listing the destination mailbox to confirm the transfer.",
        "additionalResourcesTitle": "Additional Resources",
        "additionalResourcesContent": "For more detailed information on IMAP protocols:",
        "rfcLink": "RFC 3501 - Internet Message Access Protocol - Version 4rev1",
        "implementation": "Implementation",
        "implementationContent":"The IMAP Email Transfer application is implemented using the libcurl and GTK libraries.",
        "licburlImplementation":"libcurl is a C library that facilitates easy networking operations, including sending and retrieving data over various internet protocols such as HTTP, FTP, and IMAP. In the IMAP Email Transfer application, libcurlis used to communicate with the IMAP server for sending and fetching email messages.",
        "gtkImplementation":"GTK (GIMP Toolkit) is a set of tools for creating user interfaces in C-based applications. In the IMAP Email Transfer application, GTK is utilized to create the graphical user interface (GUI) allowing users to input data, invoke email transfer operations, and display results."
    },
    pl: {
        "title": "Pomoc dotycząca transferu e-maili przez IMAP",
        "header": "Dokumentacja dotycząca transferu e-maili przez IMAP",
        "overviewTitle": "Przegląd",
        "overviewContent": "Ten dokument zapewnia podstawowe zrozumienie sposobu wykorzystania żądań IMAP w tej aplikacji do transferu e-maili między serwerami.",
        "whatIsImapTitle": "Czym jest IMAP?",
        "whatIsImapContent": "IMAP (Internet Message Access Protocol) umożliwia użytkownikom dostęp i zarządzanie swoją pocztą e-mail na zdalnym serwerze za pośrednictwem lokalnego klienta. W przeciwieństwie do POP, IMAP synchronizuje się z serwerem, co pozwala wielu klientom na widzenie tego samego stanu folderów.",
        "usingImapTitle": "Używanie IMAP w tej aplikacji",
        "usingImapIntro": "Postępuj zgodnie z tymi szczegółowymi krokami, aby skutecznie korzystać z IMAP w tej aplikacji:",
        "step1": "Podaj URL, e-mail i hasło: Rozpocznij od wpisania URL swojego serwera, adresu e-mail i hasła. Przetestuj swoje połączenie, wyświetlając listę skrzynek, aby upewnić się, że jesteś poprawnie połączony.",
        "step2": "Wyświetl listę skrzynek: Kliknij 'Lista skrzynek', aby zobaczyć listę wszystkich folderów/skrzynek. Każda skrzynka jest wyświetlana z jej atrybutami.",
        "mailboxExample1": "* LIST (\\HasNoChildren \\Drafts) \"/\" \"Drafts\": Wskazuje na folder Wersje robocze bez podfolderów.",
        "mailboxExample2": "* LIST (\\HasNoChildren) \"/\" \"INBOX\": Pokazuje INBOX, który zawiera wszystkie przychodzące e-maile.",
        "mailboxExample3": "* LIST (\\NoInferiors \\Junk) \"/\" \"Junk\": Folder Spam, który nie może zawierać podfolderów.",
        "step3": "Wybierz skrzynkę: Zazwyczaj jest to 'INBOX' dla poczty przychodzącej.",
        "step4": "Użyj poleceń IMAP: Wykonuj polecenia, aby zarządzać swoimi e-mailami. Przykłady obejmują:",
        "imapExample1": "UID SEARCH SINCE 15-Apr-2024: Szuka wszystkich e-maili otrzymanych od 15 kwietnia 2024 roku.",
        "imapExample2": "UID FETCH <UID> (RFC822) lub FETCH <UID> BODY[TEXT]: Pobiera cały e-mail odpowiadający określonemu UID.",
        "imapExample3": "UID SEARCH ALL: Znajduje wszystkie e-maile w skrzynce.",
        "imapExample4": "SEARCH FROM \"example@example.com\": Szuka wiadomości od określonego nadawcy.",
        "step5": "Zapisz e-maile: Aby zapisać e-mail, upewnij się, że masz właściwą skrzynkę i UID, a następnie użyj funkcji 'Zapisz e-mail'.",
        "step6": "Transferuj e-maile: Po zapisaniu podaj URL serwera docelowego, adres e-mail i hasło, razem ze skrzynką, do której mają być przesłane e-maile. Użyj przycisku 'Przenieś', aby zainicjować proces. Sprawdź, czy e-maile zostały przetransferowane, wyświetlając listę skrzynki docelowej.",
        "additionalResourcesTitle": "Dodatkowe zasoby",
        "additionalResourcesContent": "Aby uzyskać więcej szczegółowych informacji na temat protokołów IMAP:",
        "rfcLink": "RFC 3501 - Protokół dostępu do wiadomości internetowych - Wersja 4rev1",
        "implementation": "Implementacja",
        "implementationContent":"Aplikacja IMAP Email Transfer jest implementowana przy użyciu bibliotek libcurl i GTK.",
        "licburlImplementation":"libcurl to biblioteka C ułatwiająca operacje sieciowe, takie jak wysyłanie i pobieranie danych przez różne protokoły internetowe, takie jak HTTP, FTP i IMAP. W aplikacji \"IMAP Email Transfer\" libcurl jest używany do komunikacji z serwerem IMAP w celu wysyłania i pobierania wiadomości e-mail.",
        "gtkImplementation":"GTK (GIMP Toolkit) to zestaw narzędzi do tworzenia interfejsów użytkownika w aplikacjach opartych na C. W aplikacji \"IMAP Email Transfer\" GTK jest wykorzystywane do tworzenia graficznego interfejsu użytkownika (GUI), który umożliwia użytkownikom wprowadzanie danych, wywoływanie operacji transferu e-maili i wyświetlanie wyników."
    },
    ua: {
        "title": "Довідка з IMAP Email Transfer",
        "header": "Документація з IMAP Email Transfer",
        "overviewTitle": "Огляд",
        "overviewContent": "Цей документ надає базове розуміння того, як запити IMAP використовуються в цьому застосунку для перенесення електронних листів між серверами.",
        "whatIsImapTitle": "Що таке IMAP?",
        "whatIsImapContent": "IMAP (Протокол доступу до повідомлень в Інтернеті) дозволяє користувачам отримувати доступ та керувати своєю електронною поштою на віддаленому сервері через локального клієнта. На відміну від POP, IMAP синхронізується з сервером, що дозволяє багатьом клієнтам бачити однаковий стан папки.",
        "usingImapTitle": "Використання IMAP у цьому застосунку",
        "usingImapIntro": "Дотримуйтесь цих детальних кроків для ефективного використання IMAP у цьому застосунку:",
        "step1": "Надайте URL, електронну адресу та пароль: Почніть з введення URL вашого сервера, електронної адреси та пароля. Перевірте своє з'єднання, переглядаючи список поштових скриньок, щоб переконатися, що ви правильно підключені.",
        "step2": "Перегляньте список поштових скриньок: Клацніть 'Список поштових скриньок', щоб переглянути список всіх папок/скриньок. Кожна скринька відображається зі своїми атрибутами.",
        "mailboxExample1": "* LIST (\\HasNoChildren \\Drafts) \"/\" \"Drafts\": Вказує на папку Чернетки без підпапок.",
        "mailboxExample2": "* LIST (\\HasNoChildren) \"/\" \"INBOX\": Показує INBOX, який містить всі вхідні електронні листи.",
        "mailboxExample3": "* LIST (\\NoInferiors \\Junk) \"/\" \"Junk\": Папка Спам, яка не може містити підпапки.",
        "step3": "Виберіть поштову скриньку: Зазвичай це 'INBOX' для вхідної пошти.",
        "step4": "Використовуйте команди IMAP: Застосовуйте команди для керування своїми електронними листами. Приклади:",
        "imapExample1": "UID SEARCH SINCE 15-Apr-2024: Шукає всі електронні листи, отримані з 15 квітня 2024 року.",
        "imapExample2": "UID FETCH <UID> (RFC822) або FETCH <UID> BODY[TEXT]: Завантажує всю електронну пошту, що відповідає конкретному UID.",
        "imapExample3": "UID SEARCH ALL: Знаходить всі електронні листи у скриньці.",
        "imapExample4": "SEARCH FROM \"example@example.com\": Шукає повідомлення від конкретного відправника.",
        "step5": "Збережіть електронні листи: Щоб зберегти електронний лист, переконайтеся, що у вас є правильна поштова скринька, URL та UID, а потім використовуйте функцію 'Зберегти електронний лист'.",
        "step6": "Передача електронних листів: Після збереження надайте URL сервера призначення, електронну адресу та пароль, разом із скринькою для передачі електронних листів. Використовуйте кнопку 'Transfer', щоб ініціювати процес. Перевірте, чи електронні листи були передані, переглянувши скриньку призначення.",
        "additionalResourcesTitle": "Додаткові ресурси",
        "additionalResourcesContent": "Для отримання більш детальної інформації про протоколи IMAP:",
        "rfcLink": "RFC 3501 - Протокол доступу до повідомлень в Інтернеті - Версія 4rev1",
        "implementation": "Реалізація",
        "implementationContent":"Програма IMAP Email Transfer реалізована за допомогою бібліотек libcurl і GTK.",
        "licburlImplementation":"libcurl - це бібліотека C, яка спрощує мережеві операції, включаючи відправлення та отримання даних через різні інтернет-протоколи, такі як HTTP, FTP і IMAP. У додатку IMAP Email Transfer libcurl використовується для спілкування з сервером IMAP для відправлення та отримання електронних листів.",
        "gtkImplementation":"GTK (GIMP Toolkit)  - це набір інструментів для створення інтерфейсів користувача у програмах на базі C. У додатку IMAP Email Transfer GTK використовується для створення графічного інтерфейсу користувача (GUI), який дозволяє користувачам вводити дані, запускати операції переносу електронних листів та відображати результати."
    }
    
};
// Function to change language
function changeLanguage(lang) {
    document.querySelectorAll('[data-lang]').forEach(el => {
        const key = el.getAttribute('data-lang');
        if (languageData[lang] && languageData[lang][key]) {
            el.textContent = languageData[lang][key];
            // Reapply code tag styling to examples
            if (key.startsWith("imapExample") || key.startsWith("mailboxExample")) {
                let colonIndex = el.textContent.indexOf(':');
                if (colonIndex !== -1) {
                    let beforeColon = el.textContent.substring(0, colonIndex);
                    let afterColon = el.textContent.substring(colonIndex+1);
                    el.innerHTML = `<code>${beforeColon}</code>${afterColon}`;
                }
            }
        }
    });
    // Update URL query parameter with selected language
    const urlParams = new URLSearchParams(window.location.search);
    urlParams.set('lang', lang);
    history.replaceState({}, '', `${location.pathname}?${urlParams}`);
}

// Attach event listeners after the DOM is fully loaded
document.addEventListener('DOMContentLoaded', () => {
    const urlParams = new URLSearchParams(window.location.search);
    const langFromQuery = urlParams.get('lang');
    const langSelector = document.querySelector('.language-selector');

    // Event listener for language selector buttons
    langSelector.addEventListener('click', function(event) {
        const lang = event.target.getAttribute('data-lang-button');
        if (lang) {
            changeLanguage(lang);
        }
    });

    // Initialize the page with the language from the query parameter, or use a default language
    const initialLang = langFromQuery || (navigator.language.startsWith('pl') ? 'pl' : (navigator.language.startsWith('ua') ? 'ua' : 'en'));
    changeLanguage(initialLang);
});
