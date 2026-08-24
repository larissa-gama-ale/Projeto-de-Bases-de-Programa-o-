# 🛠️ Guia de Desenvolvimento

Este documento reúne as principais práticas que seguiremos durante o desenvolvimento da calculadora.

O objetivo é facilitar a colaboração, manter o projeto organizado e evitar conflitos de código.

> 💡 Este guia foi criado para ajudar toda a equipe, inclusive quem ainda não tem experiência com Git e GitHub.

---

## 🔄 Fluxo de Trabalho

Nosso fluxo será:

```text
Atualizar a main
      ↓
Criar uma branch
      ↓
Desenvolver
      ↓
Fazer commits
      ↓
Testar
      ↓
Enviar a branch
      ↓
Pull Request
      ↓
Revisão
      ↓
Merge na main
```

---

# 🌿 Branch Main

A `main` representa a versão principal e mais estável do projeto.

Ela deve conter código funcionando e testado.

> ⚠️ Evite desenvolver diretamente na `main`.

---

# 🌱 Branches de Desenvolvimento

Cada funcionalidade deve ser desenvolvida em uma branch própria.

### 📌 Branches previstas

```text
feature/calculadora
feature/frete
feature/terminal
feature/data-hora
feature/resumo-compra
```

Novas branches poderão ser criadas conforme as necessidades do projeto.

---

## 🏷️ Prefixos

| Prefixo | Utilização |
|---|---|
| `feature/` | Nova funcionalidade |
| `fix/` | Correção de bug |
| `refactor/` | Melhoria ou organização do código |
| `docs/` | Documentação |
| `test/` | Testes |
| `hotfix/` | Correção urgente |

### 💡 Exemplos

```text
feature/calculadora
feature/frete
feature/terminal
fix/calculo-frete
refactor/funcao-total
docs/readme
test/calculadora
hotfix/erro-calculo
```

---

# 🔄 Antes de Começar

Antes de iniciar uma nova tarefa, atualize sua branch para evitar conflitos com as alterações feitas pela equipe.

### 1. Acesse a `main`

```bash
git checkout main
```

### 2. Atualize a `main`

```bash
git pull origin main
```

### 3. Volte para sua branch

```bash
git checkout nome-da-sua-branch
```

### 4. Atualize sua branch

```bash
git merge main
```

> 💡 Substitua `nome-da-sua-branch` pelo nome da branch que você está utilizando.

---

# 💾 Commits

Um **commit** registra uma alteração realizada no projeto.

Faça commits pequenos e frequentes, representando uma etapa concluída.

### ✅ Exemplos

```text
feat: adiciona seleção de produtos
feat: implementa cálculo do frete
fix: corrige cálculo para peso acima de 2kg
docs: atualiza documentação
test: adiciona testes do frete
refactor: organiza funções da calculadora
```

### 📝 Padrão de Commit

```text
tipo: descrição curta da alteração
```

| Tipo | Utilização |
|---|---|
| `feat:` | Nova funcionalidade |
| `fix:` | Correção |
| `refactor:` | Refatoração |
| `docs:` | Documentação |
| `test:` | Testes |
| `style:` | Formatação |
| `chore:` | Manutenção |

---

# 📍 Pontos de Controle

Faça um commit sempre que uma etapa importante for concluída.

- Estrutura da calculadora
- Seleção do produto
- Cálculo do frete
- Cálculo do valor total
- Resumo da compra
- Data e hora
- Data prevista de entrega
- Interface do terminal
- Testes

Assim conseguimos acompanhar a evolução do projeto e retornar a uma versão anterior caso necessário.

---

# 📤 Enviando Alterações

Antes de enviar sua branch, verifique se:

- O programa está funcionando;
- O código está organizado;
- Os testes foram realizados;
- O commit foi realizado.

Depois, envie sua branch para o GitHub:

```bash
git push origin nome-da-sua-branch
```

> 💡 O `git push` envia os commits da sua branch local para o repositório no GitHub.

---

# 🔀 Pull Request

Quando sua funcionalidade estiver pronta, abra um **Pull Request (PR)**.

O Pull Request permite que a equipe revise o código antes que ele seja integrado à `main`.

### 🔎 Antes de criar o PR

- Verifique se o programa está funcionando;
- Teste a funcionalidade desenvolvida;
- Revise seu código;
- Atualize sua branch com a `main`, se necessário.

### 📝 Na descrição do PR

Informe:

- O que foi desenvolvido;
- O que foi alterado;
- O que precisa ser testado.

Após a revisão e aprovação da equipe, a alteração poderá ser integrada à `main`.

---

# 📁 Organização do Projeto

Para manter o projeto organizado:

- Mantenha os arquivos nas pastas corretas;
- Evite código duplicado;
- Utilize nomes claros para funções e variáveis;
- Prefira funções pequenas e organizadas;
- Evite arquivos desnecessários;
- Não altere partes importantes do projeto sem comunicar a equipe.

### 📂 Estrutura do Projeto

```text
projeto/
│
├── calculadora/
│
├── docs/
│   ├── equipe/
│   ├── calculadora/
│   ├── design/
│   └── testes/
│
├── README.md
├── LICENSE
└── .gitignore
```

---

# 🖥️ Interface do Terminal

A calculadora será executada pelo terminal e deverá possuir uma interface organizada e fácil de utilizar.

A equipe definirá um padrão visual para manter as telas consistentes.

## 🎨 Padrão da Interface

A interface deverá utilizar:

- Cabeçalhos organizados;
- Linhas separadoras;
- Menus numerados;
- Mensagens claras;
- Organização das informações;
- Resumo da compra bem apresentado;
- Padrão visual semelhante em todas as telas.

### 💡 Exemplo de Interface

```text
==================================================
              CALCULADORA DE COMPRAS
==================================================

              SELECIONE UM PRODUTO

[1] Smartphone
[2] Notebook
[3] Fone de Ouvido
[4] Teclado
[5] Mouse

--------------------------------------------------
Digite o código do produto:
```

O objetivo é criar uma experiência simples, organizada e agradável, mesmo utilizando apenas o terminal.

---

# 💬 Comunicação

A comunicação é essencial para o desenvolvimento em equipe.

Se uma alteração puder afetar o trabalho de outro integrante, converse com a equipe antes de modificar.

### 💡 Durante o Desenvolvimento

- Se tiver dúvidas, **pergunte**;
- Se encontrar um problema, **comunique**;
- Se encontrar uma melhoria, **compartilhe**;
- Se puder ajudar alguém, **ajude**.

Uma boa comunicação evita conflitos e retrabalho.

---

# 🎯 Nosso Objetivo

Mais importante do que escrever muito código é escrever um código que qualquer integrante consiga entender.

Buscamos:

- ✨ Clareza
- 📁 Organização
- 🤝 Colaboração
- 📚 Aprendizado

Construir um bom projeto é um trabalho coletivo.

---

# 🌱 Filosofia do Projeto

> **Errar faz parte do processo.**

Não esperamos que todos saibam tudo desde o início.

Nosso objetivo é aprender, ajudar uns aos outros e evoluir juntos durante o desenvolvimento.

> 💬 Se tiver dúvidas, pergunte.
>
> 💡 Se encontrar uma melhoria, compartilhe.
>
> 🤝 Se puder ajudar alguém da equipe, ajude.
>
> 📚 Se aprender algo novo, compartilhe.

Nosso objetivo é **evoluir juntos enquanto construímos uma calculadora bem estruturada, funcional e organizada.**

---

<div align="center">

# 🧮 Calculadora em C

**Bases de Programação • Projeto Acadêmico**

Desenvolvido pela equipe 💻

</div>
