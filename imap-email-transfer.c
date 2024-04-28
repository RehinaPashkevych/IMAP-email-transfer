/*
COMPILATION:
        gcc `pkg-config --cflags --libs gtk4` -o imap  imap-email-transfer.c -lcurl 

USAGE:
     ./imap
*/

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>


typedef struct {
    GtkWidget *email;
    GtkWidget *password;
    GtkWidget *url;
    GtkWidget *mailbox;
    GtkWidget *request;
    GtkWidget *output; 
    GtkWidget *uid;    
    GtkEntryBuffer *email_buffer;
    GtkEntryBuffer *password_buffer;
    GtkEntryBuffer *url_buffer;
    GtkEntryBuffer *UID_buffer;
    GtkEntryBuffer *mailbox_buffer;
    GtkEntryBuffer *request_buffer;
    GtkEntryBuffer *output_buffer;
} EmailServerDetails;

// Global variables for server details
EmailServerDetails from_server_details;
EmailServerDetails to_server_details;

static void on_list_mailboxes_clicked(GtkWidget *widget, gpointer data);
static void on_run_clicked(GtkWidget *widget, gpointer data);
static void on_save_clicked(GtkWidget *widget, gpointer data);
static void on_transfer_clicked(GtkWidget *widget, gpointer data);
static void on_clear_output_clicked(GtkWidget *widget, gpointer data);

static void init_email_server_details(EmailServerDetails *details, GtkWidget *grid, gint row_offset, const gchar *label_text);
static void open_help(GtkWidget *widget, gpointer app); 
int upload_email(const char* url, const char* username, const char* password, const char* mailbox, const char* emailPath, GtkWidget *output);
void fetch_email_and_save_to_file(const char *imap_url, const char* mailbox, const char *username, const char *password, const char *email_uid, GtkWidget *output);


// GTK application activate callback
static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "IMAP Email Transfer");
    gtk_window_set_default_size(GTK_WINDOW(window), 1200, 800);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);  // Prevent resizing

    // Create a vertical box to act as the main layout container
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child(GTK_WINDOW(window), vbox);

    // Create a horizontal box to act as the toolbar
    GtkWidget *toolbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX(vbox), toolbar);

    // Create a help button and add it to the toolbar
    GtkWidget *help_button = gtk_button_new_with_label("Help");
    gtk_box_append(GTK_BOX(toolbar), help_button);
    gtk_widget_set_margin_end(help_button, 10);
    g_signal_connect(help_button, "clicked", G_CALLBACK(open_help), NULL);

    GtkWidget *clear_output_button = gtk_button_new_with_label("Clear");
    gtk_box_append(GTK_BOX(toolbar), clear_output_button);
    g_signal_connect(clear_output_button, "clicked", G_CALLBACK(on_clear_output_clicked), &from_server_details);
    g_signal_connect(clear_output_button, "clicked", G_CALLBACK(on_clear_output_clicked), &to_server_details);

    // Create a grid and add it to the vbox, not directly to the window
    GtkWidget *grid = gtk_grid_new();
    gtk_box_append(GTK_BOX(vbox), grid);  // Append grid to vbox

    // Initialize "From" and "To" server details
    init_email_server_details(&from_server_details, grid, 0, "From");
    init_email_server_details(&to_server_details, grid, 12, "To"); // Increased spacing between servers

    // Buttons for 'list of mailboxes' and 'run'
    GtkWidget *list_mailboxes_button_from = gtk_button_new_with_label("List of Mailboxes");
    gtk_widget_set_margin_end(list_mailboxes_button_from, 60);
    gtk_widget_set_margin_start(list_mailboxes_button_from, 10);
    g_signal_connect(list_mailboxes_button_from, "clicked", G_CALLBACK(on_list_mailboxes_clicked), &from_server_details);
    gtk_grid_attach(GTK_GRID(grid), list_mailboxes_button_from, 1, 8, 1, 1);

    GtkWidget *run_button_from = gtk_button_new_with_label("Run");
    gtk_widget_set_margin_end(run_button_from, 60);
    gtk_widget_set_margin_start(run_button_from, 10);
    g_signal_connect(run_button_from, "clicked", G_CALLBACK(on_run_clicked), &from_server_details);
    gtk_grid_attach(GTK_GRID(grid), run_button_from, 1, 9, 1, 1);

    GtkWidget *save_from = gtk_button_new_with_label("Save email");
    gtk_widget_set_margin_end(save_from, 60);
    gtk_widget_set_margin_start(save_from, 10);
    g_signal_connect(save_from, "clicked", G_CALLBACK(on_save_clicked), &from_server_details);
    gtk_grid_attach(GTK_GRID(grid), save_from, 1, 10, 1, 1);

    GtkWidget *list_mailboxes_button_to = gtk_button_new_with_label("List of Mailboxes");
    gtk_widget_set_margin_end(list_mailboxes_button_to, 60);
    gtk_widget_set_margin_start(list_mailboxes_button_to, 10);
    g_signal_connect(list_mailboxes_button_to, "clicked", G_CALLBACK(on_list_mailboxes_clicked), &to_server_details);
    gtk_grid_attach(GTK_GRID(grid), list_mailboxes_button_to, 1, 20, 1, 1);

    GtkWidget *run_button_to = gtk_button_new_with_label("Run");
    g_signal_connect(run_button_to, "clicked", G_CALLBACK(on_run_clicked), &to_server_details);
    gtk_widget_set_margin_end(run_button_to, 60);
    gtk_widget_set_margin_start(run_button_to, 10);
    gtk_grid_attach(GTK_GRID(grid), run_button_to, 1, 21, 1, 1);

    GtkWidget *save_to = gtk_button_new_with_label("Save email");
    gtk_widget_set_margin_end(save_to, 60);
    gtk_widget_set_margin_start(save_to, 10);
    g_signal_connect(save_to, "clicked", G_CALLBACK(on_save_clicked), &to_server_details);
    gtk_grid_attach(GTK_GRID(grid), save_to, 1, 22, 1, 1);

    GtkWidget *transfer = gtk_button_new_with_label("Transfer");
    gtk_widget_set_margin_end(transfer, 60);
    gtk_widget_set_margin_start(transfer, 10);
    g_signal_connect(transfer, "clicked", G_CALLBACK(on_transfer_clicked), &to_server_details);
    gtk_grid_attach(GTK_GRID(grid), transfer, 1, 23, 1, 1);

    gtk_widget_show(window);
}


int main(int argc, char *argv[]) {
    GtkApplication *app = gtk_application_new("org.gtk.imap-transfer", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}

static void init_email_server_details(EmailServerDetails *details, GtkWidget *grid, gint row_offset, const gchar *label_text) {
    GtkWidget *label = gtk_label_new(label_text);
    gtk_grid_attach(GTK_GRID(grid), label, 0, row_offset, 2, 1); // Label spans two columns for better alignment

    int entry_width = 150;  // Define a base width for entries

    // Set up the email field with margins
    GtkWidget *label_email = gtk_label_new("Email:");
    gtk_grid_attach(GTK_GRID(grid), label_email, 0, row_offset + 1, 1, 1);
    details->email_buffer = gtk_entry_buffer_new(NULL, 0);
    details->email = gtk_entry_new_with_buffer(details->email_buffer);
    gtk_widget_set_size_request(details->email, entry_width *2, -1);
    gtk_widget_set_margin_start(details->email, 10); // Add left margin
    gtk_widget_set_margin_end(details->email, 60);   // Add right margin
    gtk_widget_set_hexpand(details->email, FALSE);
    gtk_grid_attach(GTK_GRID(grid), details->email, 1, row_offset + 1, 1, 1);

    label = gtk_label_new("Password:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, row_offset + 2, 1, 1);
    details->password_buffer = gtk_entry_buffer_new(NULL, 0);
    details->password = gtk_entry_new_with_buffer(details->password_buffer);
    gtk_widget_set_margin_start(details->password, 10); // Add left margin
    gtk_widget_set_margin_end(details->password, 60);   // Add right margin
    gtk_entry_set_visibility(GTK_ENTRY(details->password), FALSE);
    gtk_widget_set_size_request(details->password, entry_width * 2, 1); // Set double the base width
    gtk_widget_set_hexpand(details->password, FALSE);
    gtk_grid_attach(GTK_GRID(grid), details->password, 1, row_offset + 2, 2, 1);

    label = gtk_label_new("URL:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, row_offset + 3, 1, 1);
    details->url_buffer = gtk_entry_buffer_new(NULL, 0);
    details->url = gtk_entry_new_with_buffer(details->url_buffer);
    gtk_widget_set_size_request(details->url, entry_width * 2, 1); // Set double the base width
    gtk_widget_set_margin_start(details->url, 10); // Add left margin
    gtk_widget_set_margin_end(details->url, 60);   // Add right margin
    gtk_grid_attach(GTK_GRID(grid), details->url, 1, row_offset + 3, 2, 1);

    label = gtk_label_new("Mailbox:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, row_offset + 5, 1, 1);
    details->mailbox_buffer = gtk_entry_buffer_new(NULL, 0);
    details->mailbox = gtk_entry_new_with_buffer(details->mailbox_buffer);
    gtk_widget_set_size_request(details->mailbox, entry_width * 2, 1); // Set double the base width
    gtk_widget_set_margin_start(details->mailbox, 10); // Add left margin
    gtk_widget_set_margin_end(details->mailbox, 60);   // Add right margin
    gtk_grid_attach(GTK_GRID(grid), details->mailbox, 1, row_offset + 5, 2, 1);

    label = gtk_label_new("Request:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, row_offset + 6, 1, 1);
    details->request_buffer = gtk_entry_buffer_new(NULL, 0);
    details->request = gtk_entry_new_with_buffer(details->request_buffer);
    gtk_widget_set_size_request(details->request, entry_width * 2, 1); // Set double the base width
    gtk_widget_set_margin_start(details->request, 10); // Add left margin
    gtk_widget_set_margin_end(details->request, 60);   // Add right margin
    gtk_grid_attach(GTK_GRID(grid), details->request, 1, row_offset + 6, 2, 1);


    label = gtk_label_new("UID:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, row_offset + 7, 1, 1);
    details->UID_buffer = gtk_entry_buffer_new(NULL, 0);
    details->uid = gtk_entry_new_with_buffer(details->UID_buffer);
    gtk_widget_set_size_request(details->uid, entry_width * 2, 1); // Set double the base width
    gtk_widget_set_margin_start(details->uid, 10); // Add left margin
    gtk_widget_set_margin_end(details->uid, 60);   // Add right margin
    gtk_grid_attach(GTK_GRID(grid), details->uid, 1, row_offset + 7, 2, 1);

    // Output field to display provided details
    details->output = gtk_label_new("");
    gtk_widget_set_size_request(details->output, 370 , -1);  // Set fixed width for the output, adjust as necessary
    // Place output at the top of 'grid2'
    gtk_grid_attach(GTK_GRID(grid), details->output, 6, row_offset + 1, 3, 1);  // Span 3 columns, place in first row
}


// ----------------------CALBACKS-----------REQUESTS---------------

// Funkcja callback do zapisu danych do pliku
static size_t write_data_to_file(void *buffer, size_t size, size_t nmemb, FILE *file, gpointer userdata) {
    fwrite(buffer, size, nmemb, file);
    return size * nmemb;
}

static size_t write_callback(char *buffer, size_t size, size_t nmemb, gpointer userdata) {
    GtkWidget *output_label = (GtkWidget *)userdata;
    const char *current_text = gtk_label_get_text(GTK_LABEL(output_label));
    if (current_text == NULL || strlen(current_text) == 0) {
        // If current label is empty, set new text
        gtk_label_set_text(GTK_LABEL(output_label), buffer);
    } 
    fwrite(buffer, size, nmemb, stdout);
    return size * nmemb;
}

void perform_curl_request(const char* url, const char* mailbox, const char* username, const char* password, const char* request, GtkWidget *output) {
    CURL *curl;
    CURLcode res;
    char fullUrl[1024];
    snprintf(fullUrl, sizeof(fullUrl), "%s/%s", url, mailbox);

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_USERNAME, username);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
        curl_easy_setopt(curl, CURLOPT_URL, fullUrl);
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, output);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, request);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            char error_msg[256];
            snprintf(error_msg, sizeof(error_msg), "Curl error: %s", curl_easy_strerror(res));
            gtk_label_set_text(GTK_LABEL(output), error_msg);
        }

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}



//======================================BUTTON  FUNCTIONS==========================


static void on_transfer_clicked(GtkWidget *widget, gpointer data) {
    EmailServerDetails *details = (EmailServerDetails *) data;
    const char *url = gtk_entry_buffer_get_text(details->url_buffer);
    const char *username = gtk_entry_buffer_get_text(details->email_buffer);
    const char *password = gtk_entry_buffer_get_text(details->password_buffer);
    const char *mailbox = gtk_entry_buffer_get_text(details->mailbox_buffer);

    if (username && url && password && mailbox) {
       upload_email(url, username, password, mailbox, "email.eml", details->output);
    } else {
        gtk_label_set_text(GTK_LABEL(details->output), "Error: Missing required input");
    }
}

static void on_list_mailboxes_clicked(GtkWidget *widget, gpointer data) {
    EmailServerDetails *details = (EmailServerDetails *) data;
    const char *url = gtk_entry_buffer_get_text(details->url_buffer);
    const char *username = gtk_entry_buffer_get_text(details->email_buffer);
    const char *password = gtk_entry_buffer_get_text(details->password_buffer);
    const char *mailbox = "";

    if (username && url && password ) {
        gtk_label_set_text(GTK_LABEL(details->output), "");
        perform_curl_request(url, mailbox, username, password, "LIST \"\" *", details->output);
    } else {
        gtk_label_set_text(GTK_LABEL(details->output), "Error: Missing required input");
    }
}


static void on_run_clicked(GtkWidget *widget, gpointer data) {
    EmailServerDetails *details = (EmailServerDetails *) data;
    const char *url = gtk_entry_buffer_get_text(details->url_buffer);
    const char *username = gtk_entry_buffer_get_text(details->email_buffer);
    const char *password = gtk_entry_buffer_get_text(details->password_buffer);
    const char *mailbox = gtk_entry_buffer_get_text(details->mailbox_buffer);
    const char *query = gtk_entry_buffer_get_text(details->request_buffer);

    if (username && url && password && query) {
      gtk_label_set_text(GTK_LABEL(details->output), "");
      perform_curl_request(url, mailbox, username, password, query, details->output);
    } else {
        gtk_label_set_text(GTK_LABEL(details->output), "Error: Missing required input");
    }
}

static void on_clear_output_clicked(GtkWidget *widget, gpointer data) {
    EmailServerDetails *details = (EmailServerDetails *)data;
    // Clear the output label text for the provided EmailServerDetails
    gtk_label_set_text(GTK_LABEL(details->output), "");
}


// Helper function to read and display the body of an email
static void display_email_body(GtkLabel *output_label, const char *filename) {
    if (!g_file_test(filename, G_FILE_TEST_EXISTS | G_FILE_TEST_IS_REGULAR)) {
        gtk_label_set_text(output_label, "Email file does not exist.");
        return;
    }

    FILE *file = fopen(filename, "r");
    if (!file) {
        gtk_label_set_text(output_label, "Failed to open the email file.");
        return;
    }

    char buffer[1024];  // Buffer size remains 1024 to accommodate large lines
    int is_body = 0;
    GString *body_content = g_string_new("");
    int line_count = 0;
    const int max_lines = 20;  // Maximum number of lines to display

    while (fgets(buffer, sizeof(buffer), file) != NULL && line_count < max_lines) {
        if (strstr(buffer, "Content-Type: text/plain") != NULL ||
            strstr(buffer, "Content-Type: text/html") != NULL) {
            is_body = 1;
            continue;
        }
        if (is_body) {
            if (strstr(buffer, "--") == buffer) {
                break; // Assume MIME boundary indicates end of the relevant part
            }
            if (buffer[0] == '\r' || buffer[0] == '\n') {
                continue; // Skip initial new lines in the body
            }
            g_string_append(body_content, buffer);
            line_count++;  // Increment line count for each added line
        }
    }

    fclose(file);
    gtk_label_set_text(output_label, body_content->str);
    g_string_free(body_content, TRUE);
}


// Callback function triggered when "Save" button is clicked
static void on_save_clicked(GtkWidget *widget, gpointer data) {
    EmailServerDetails *details = (EmailServerDetails *)data;
    const char *url = gtk_entry_buffer_get_text(details->url_buffer);
    const char *username = gtk_entry_buffer_get_text(details->email_buffer);
    const char *password = gtk_entry_buffer_get_text(details->password_buffer);
    const char *mailbox = gtk_entry_buffer_get_text(details->mailbox_buffer);
    const char *uid = gtk_entry_buffer_get_text(details->UID_buffer);

    printf("url: %s\n", url);
    printf("uusernamerl: %s\n", username);

    // Improved check to include empty strings
    if (!username || strlen(username) == 0 ||
        !url || strlen(url) == 0 ||
        !password || strlen(password) == 0 ||
        !mailbox || strlen(mailbox) == 0 ||
        !uid || strlen(uid) == 0) {
        gtk_label_set_text(GTK_LABEL(details->output), "Error: Missing required input.");
        return; // Prevent further processing if any field is missing or empty
    }

    fetch_email_and_save_to_file(url, mailbox, username, password, uid, details->output);
    display_email_body(GTK_LABEL(details->output), "email.eml");
}


// Callback function to open help documentation using a web browser
static void open_help(GtkWidget *widget, gpointer app) {
    // Get the current working directory
    gchar *cwd = g_get_current_dir();
    // Construct the full path to the help document
    gchar *path_to_help = g_build_filename(cwd, "index.html", NULL);
    gchar *uri = g_strdup_printf("file://%s", path_to_help);

    // Use xdg-open to handle the URI
    gchar *command = g_strdup_printf("xdg-open %s", uri);
    system(command); // Use the system function to execute the command

    // Free all dynamically allocated memory
    g_free(command);
    g_free(uri);
    g_free(path_to_help);
    g_free(cwd);
}


// Funkcja do pobierania e-maila z serwera źródłowego i zapisywania go do pliku
void fetch_email_and_save_to_file(const char *imap_url, const char* mailbox, const char *username, const char *password, const char *email_uid, GtkWidget *output) {
    CURL *curl;
    FILE *file;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        file = fopen("email.eml", "wb");
        if(!file) {
            perror("Cannot open file email.eml");
            gtk_label_set_text(GTK_LABEL(output), "Cannot open file email.eml");
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return;
        }

        char fullUrl[1024];
        snprintf(fullUrl, sizeof(fullUrl), "%s/%s;UID=%s", imap_url, mailbox, email_uid);
        printf("URL being requested: %s\n", fullUrl);

        curl_easy_setopt(curl, CURLOPT_USERNAME, username);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
        curl_easy_setopt(curl, CURLOPT_URL, fullUrl);
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data_to_file);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            char error_msg[256];
            snprintf(error_msg, sizeof(error_msg), "Curl error: %s", curl_easy_strerror(res));
            gtk_label_set_text(GTK_LABEL(output), error_msg);
            printf("Curl error: %s\n", curl_easy_strerror(res));
        }

        fclose(file);
        curl_easy_cleanup(curl);
    } else {
        gtk_label_set_text(GTK_LABEL(output), "Failed to initialize cURL.");
    }
    curl_global_cleanup();
}




int upload_email(const char* url, const char* username, const char* password, const char* mailbox, const char* emailPath, GtkWidget *output) {
    CURL *curl;
    CURLcode res;
    FILE *emailFile;

    // Open the file containing the email to upload
    emailFile = fopen(emailPath, "rb");
    if (!emailFile) {
        perror("Failed to open file");
        return 1;
    }

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        // Set destination URL (IMAP server and mailbox to append the email)
        char fullUrl[1024];
        snprintf(fullUrl, sizeof(fullUrl), "%s/%s", url, mailbox); 
        curl_easy_setopt(curl, CURLOPT_URL, fullUrl);

        // Set username and password for destination server
        curl_easy_setopt(curl, CURLOPT_USERNAME, username);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password);

        // Set the read callback function and data
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, fread);
        curl_easy_setopt(curl, CURLOPT_READDATA, emailFile);
        
        // Enable uploading
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        // Determine and set the size of the file to upload
        fseek(emailFile, 0L, SEEK_END);
        long fileSize = ftell(emailFile);
        curl_easy_setopt(curl, CURLOPT_INFILESIZE, fileSize);
        rewind(emailFile);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            char error_msg[256];
            snprintf(error_msg, sizeof(error_msg), "Curl error: %s", curl_easy_strerror(res));
            gtk_label_set_text(GTK_LABEL(output), error_msg);
        }

        gtk_label_set_text(GTK_LABEL(output), "The email was transfered successefully!");
        curl_easy_cleanup(curl);
    }

    fclose(emailFile);
    curl_global_cleanup();

    return (int)res;
}