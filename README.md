weatherTB

Aplicativo para mostrar a previsão do tempo na barra de tarefas do windows.
Implementado utilizando o framework Qt.
As informações do clima são extraídas do site [www.wttr.in]

TODO:
  Mostrar previsão como um 'browser' -- DONE
  Configurar local padrão e salvar -- DONE
  Baixar html para não precisar acessar o site toda vez -- DONE
  Implementar thread concorrente para avaliar idade do arquivo html e baixar se necessário -- DONE
      |- TORNAR O DOWNLOAD DO ARQUIVO SÍNCRONO --
  Parsear somente as informações necessárias do html --
      |- Formatar string --
  Mostrar na barra --
