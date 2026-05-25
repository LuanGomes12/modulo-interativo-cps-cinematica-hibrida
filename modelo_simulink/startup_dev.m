% startup.m - Executa automaticamente ao abrir o MATLAB nesta pasta
% Isso garante que o App Designer encontre as imagens ANTES de tentar desenhar

disp('🔧 Configurando ambiente do Manipula.EDU...');

% Pega a pasta atual
pastaAtual = pwd;

% Adiciona a pasta atual e TODAS as subpastas (App, Imagens, etc) ao caminho
addpath(genpath(pastaAtual));

disp('✅ Caminhos carregados! Pode rodar o Splash.');