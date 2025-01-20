alert ('Digite a senha do sistema' );
let senhaDoSistema = "casa";
let senha; 
let Tentativas = 1;
let TentativasMax = 3;

while (Tentativas <= TentativasMax) {
    senha = prompt("Digite a senha do sistema:");

if (senha == senhaDoSistema){
    alert("Acesso ao sistema garantido");
    break;
}else {
    alert(`senha incorreta ${Tentativas} de ${TentativasMax}.`);
    Tentativas++ ;


    
}
}

