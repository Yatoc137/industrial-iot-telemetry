# Instalação e ativação do ambiente

### Instalação do Poetry
```bash
pip install pipx
pipx ensurepath
pipx install poetry
```

Verifique:
```bash
poetry --version
```

### Instalando as dependências

O comando precisa ser executado nesse diretório:
`.../backend/python-backend/`

```bash
poetry install
```

### Ativando o ambiente virtual:
```bash
poetry shell
```


### Executando a API:
```bash
task run
```
