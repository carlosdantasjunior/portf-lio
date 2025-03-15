// Criação de uma lista para armazenar os nomes dos amigos
let amigos = [];

// Função para adicionar um nome à lista de amigos
function adicionarAmigo() {
    const inputNome = document.getElementById('amigo');
    const nome = inputNome.value.trim();

    if (nome !== "") {
        amigos.push(nome);
        inputNome.value = ''; // Limpa o campo de input após adicionar
        atualizarListaAmigos();
    }
}

// Função para atualizar a lista exibida na tela
function atualizarListaAmigos() {
    const listaAmigos = document.getElementById('listaAmigos');
    listaAmigos.innerHTML = ''; // Limpa a lista antes de atualizar

    amigos.forEach(nome => {
        const li = document.createElement('li');
        li.textContent = nome;
        listaAmigos.appendChild(li);
    });
}

// Função para sortear um amigo secreto aleatoriamente
function sortearAmigo() {
    if (amigos.length < 2) {
        alert('É necessário pelo menos 2 amigos para realizar o sorteio!');
        return;
    }

    // Embaralhar a lista de amigos
    const amigosEmbaralhados = [...amigos];
    for (let i = amigosEmbaralhados.length - 1; i > 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));
        [amigosEmbaralhados[i], amigosEmbaralhados[j]] = [amigosEmbaralhados[j], amigosEmbaralhados[i]];
    }

    // Exibir os resultados do sorteio
    const resultado = document.getElementById('resultado');
    resultado.innerHTML = ''; // Limpa a lista de resultados

    amigos.forEach((nome, index) => {
        const li = document.createElement('li');
        li.textContent = `${nome} sorteou ${amigosEmbaralhados[index]}`;
        resultado.appendChild(li);
    });
}

// Função para sortear um amigo secreto e exibir apenas um sorteio por vez
let indiceSorteio = 0; // Variável para controlar o índice do sorteio atual

function sortearAmigo() {
    if (amigos.length < 2) {
        alert('É necessário pelo menos 2 amigos para realizar o sorteio!');
        return;
    }

    // Embaralhar a lista de amigos
    const amigosEmbaralhados = [...amigos];
    for (let i = amigosEmbaralhados.length - 1; i > 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));
        [amigosEmbaralhados[i], amigosEmbaralhados[j]] = [amigosEmbaralhados[j], amigosEmbaralhados[i]];
    }

    // Exibir apenas um sorteio de cada vez
    const resultado = document.getElementById('resultado');
    const li = document.createElement('li');
    
    // Verificar se todos os amigos já foram sorteados
    if (indiceSorteio < amigos.length) {
        li.textContent = amigosEmbaralhados[indiceSorteio]; // Exibe apenas o nome do sorteado
        resultado.innerHTML = ''; // Limpar o conteúdo anterior
        resultado.appendChild(li);
        indiceSorteio++; // Avançar para o próximo sorteio
    } else {
        alert('Todos os amigos foram sorteados!');
    }
}
