# 📝 Sistema de Cadastro com Interface Gráfica (GTK + Glade + C)

Este projeto demonstra a criação de uma interface gráfica simples em **C**, utilizando **GTK** e **Glade**. O sistema permite o cadastro e a listagem de usuários com os campos **nome** e **e-mail**.

## 🚀 Funcionalidades

- Tela de login (usuário: `admin`, senha: `admin`)
- Tela de cadastro de usuários
- Tela de listagem de usuários cadastrados
- Validação de campos obrigatórios
- Interface criada com Glade
- Estrutura de dados com lista encadeada

## 🖼️ Telas do Sistema

- **Login:** Acesso ao sistema
- **Cadastro:** Inserção de nome e e-mail
- **Listagem:** Visualização dos dados cadastrados

## 📁 Estrutura

```bash
.
├── interface.glade       # Interface gráfica feita no Glade
├── main.c                # Código-fonte em C
├── README.md             # Este arquivo

```
## 📃 Compilação
- gcc main.c -o sistema `pkg-config --cflags --libs gtk+-3.0`

## 💻 Execução
- ./sistema
