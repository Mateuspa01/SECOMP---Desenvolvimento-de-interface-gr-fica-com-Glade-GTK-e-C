#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdbool.h>

// Widgets globais
GtkBuilder *builder;
GtkWidget *window;
GtkStack *stack;
GtkListStore *modelo_armazenamento;

typedef struct usuario{
    int id;
    char nome[100];
    char email[100];
    struct usuario *proximo;
} user;

int id = 0;
user *cabecalho_user;
user *proximo_user;

void on_main_window_destroy();

void on_button_cadastrar_clicked(GtkButton *button, gpointer user_data) {
    gtk_main_quit();
}

void mensagem(const gchar *text, const gchar *secondary_text,const gchar *icon_name){
    GtkDialog *mensagem_dialogo = GTK_DIALOG(gtk_builder_get_object(builder, "mensagem"));

    gtk_message_dialog_set_markup(GTK_MESSAGE_DIALOG(mensagem_dialogo), text);
    gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(mensagem_dialogo), secondary_text);
    //gtk_message_dialog_set_image(GTK_MESSAGE_DIALOG(mensagem_dialogo),gtk_image_new_from_icon_name(icon_name, GTK_ICON_SIZE_DIALOG));

    gtk_widget_show_all(GTK_WIDGET(mensagem_dialogo));
    gtk_dialog_run(mensagem_dialogo);
    gtk_widget_hide(GTK_WIDGET(mensagem_dialogo));
}

void login(const gchar *email,const gchar *senha, gboolean lembrar){
    if((strcmp(email, "admin")) == 0 && (strcmp(senha, "admin")) == 0){
        mensagem("Bem-Vindo", "Usuario Logado com sucesso!", "emblem-default");
        gtk_stack_set_visible_child_name(stack, "view_listar");
    }else{
        mensagem("Erro!", "Email ou senha incorretos!", "dialog-error");
    }
}

void on_button_login_clicked(GtkButton *button, gpointer user_data) {
    
    GtkEntry *entry_email = GTK_ENTRY(gtk_builder_get_object(builder, "email"));
    const gchar *email = gtk_entry_get_text(entry_email);

    GtkEntry *entry_senha = GTK_ENTRY(gtk_builder_get_object(builder, "senha"));
    const gchar *senha = gtk_entry_get_text(entry_senha);

    GtkToggleButton *check_lembrar = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "checklembrar"));
    gboolean marcado = gtk_toggle_button_get_active(check_lembrar);

    login(email, senha, marcado);
}

void on_button_cad_listar_clicked(GtkButton *button, gpointer user_data) {
    gtk_stack_set_visible_child_name(stack, "view_cadastro");
}

void on_button_sair_inicial_clicked(GtkButton *button, gpointer user_data) {
    gtk_stack_set_visible_child_name(stack, "view_login");
}

void on_button_cad_voltar_clicked(GtkButton *button, gpointer user_data) {
    gtk_stack_set_visible_child_name(stack, "view_listar");
}

void on_button_listar_voltar_clicked(GtkButton *button, gpointer user_data) {
    gtk_stack_set_visible_child_name(stack, "view_login");
}

void on_button_listar_clicked(GtkButton *button, gpointer user_data) {
    proximo_user->proximo = NULL;
    proximo_user = cabecalho_user;

    GtkTreeIter iter;
    gtk_list_store_clear(modelo_armazenamento);

    while(proximo_user->proximo != NULL){
        gtk_list_store_append(modelo_armazenamento, &iter);
        gtk_list_store_set(modelo_armazenamento, &iter, 
            0, proximo_user->id, 
            1, proximo_user->nome, 
            2, proximo_user->email, 
            -1);

        proximo_user = proximo_user->proximo;
    }
}

void on_button_cad_cadastrar_clicked(GtkButton *button, gpointer user_data) {
    GtkEntry *entry_cad_nome = GTK_ENTRY(gtk_builder_get_object(builder, "cad_nome"));
    const gchar *cad_nome = gtk_entry_get_text(entry_cad_nome);

    GtkEntry *entry_cad_email = GTK_ENTRY(gtk_builder_get_object(builder, "cad_email"));
    const gchar *cad_email = gtk_entry_get_text(entry_cad_email);

    if(strcmp(cad_nome, "") == 0){
        mensagem("Aviso", "Campo 'Nome' obrigatório!", "dialog-error");
    }else{
        id++;
        proximo_user->id = id;
        strcpy(proximo_user->nome, cad_nome);
        strcpy(proximo_user->email, cad_email);

        gchar texto[100];
        g_snprintf(texto, 100, "%s%s%s", "Usuario ", proximo_user->nome, " cadastrado!");
        mensagem("Aviso", texto, "dialog-emblem-default");
        
        proximo_user->proximo = (user *)malloc(sizeof(user));
        proximo_user = proximo_user->proximo;
    }
}

int main(int argc, char *argv[]) {
    cabecalho_user = (user *)malloc(sizeof(user));
    proximo_user = cabecalho_user;

    gtk_init(&argc, &argv);

    // Carrega o arquivo Glade
    builder = gtk_builder_new_from_file("interface.glade");

    // Pega a janela principal
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    stack = GTK_STACK(gtk_builder_get_object(builder, "stack"));
    modelo_armazenamento = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore1"));

    gtk_builder_add_callback_symbols(
        builder,
        "on_button_login_clicked", G_CALLBACK(on_button_login_clicked),
        "on_main_window_destroy", G_CALLBACK(on_main_window_destroy),
        "on_button_cad_listar_clicked", G_CALLBACK(on_button_cad_listar_clicked),
        "on_button_cad_voltar_clicked", G_CALLBACK(on_button_cad_voltar_clicked),
        "on_button_listar_voltar_clicked", G_CALLBACK(on_button_listar_voltar_clicked),
        "on_button_cadastrar_clicked", G_CALLBACK(on_button_cadastrar_clicked),
        "on_button_listar_clicked", G_CALLBACK(on_button_listar_clicked),
        "on_button_cad_cadastrar_clicked", G_CALLBACK(on_button_cad_cadastrar_clicked),
        NULL);

    // Conecta os sinais
    gtk_builder_connect_signals(builder, NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

// Handler para fechar a janela
void on_main_window_destroy() {
    gtk_main_quit();
}
