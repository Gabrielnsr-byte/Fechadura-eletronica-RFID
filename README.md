Fechadura eletrônica com RFID
1.	Obejetivo geral
Este projeto visa desenvolver uma fechadura eletrônica utilizando um sistema de indentificação por radiofrequência (RFID) em conjunto com um microcontralador arduino, oferecendo segurança e praticidade. 
2.	Descrição
Este projeto consiste em uma fechadura eletrônica controlada por um sistema de RFID (Radio Frequency Identification) que utiliza um microcontrolador Arduino para gerenciar o acesso. Um módulo RFID permite que o reconhecimento de tags específicas (cartões ou chaveiros RFID) e, ao considerar uma tag autorizada, aciona a abertura da fechadura eletrônica, permitindo o acesso ao local desejado.
3.	Organização eletrônica
   
3.1	Componentes necessários
Arduino UNO: controlador principal do sistema.

Módulo leitor RFID RC522: responsável pela leitura e identificação das RFID.

Tags RFID: um cartão que contêm identificadores únicos.

Servo motor: dispositivo que aciona a abertura e fechamento da fechadura.

LED verde: indica acesso autorizado.

LED vermelho:  indica acesso negado.

Sensor Ultrassônico: detecta a proximidade de obejto ou pessoa.

Módulo bluetooth: permite a abertura e fechamento da fechadura
 
Display IC2: mostra informações sobre status de acesso, indicando se foi ou não autorizado

Push button: ao ser pressionado, aciona o fechamento manual da fechadura

4.	Descrição do algoritmo
   
4.1	Funcionamento do sistema 
Inicialização: 
O sistema inicializa o módulo RFID , ajusta o pino do servo motor. 
O display exibe uma mensagem “Leitor RFID pronto !” para indicar que o sistema ativo está pronto para uso.
O sevo motor está configurado na posição inicial, de trancamento da fechadura.
O led vermelho acende para indicar que a fechadura está trancada.

Detecção de proximidade com sensor ultrassônico:
O sensor ultrassônico mede continuamente a distância de objetos à frente. Se a distância for inferior ao valor definido em MAX_DISTANCE(20 cm), o sistema exibe no monitor serial a distância do usuário.

Leitura e verificação de Tag RFID:
Quando uma nova tag RFID não cadastrada se aproxima do leitor, o sistema lê o UID da tag e compara com o UID autorizado. Se a Tag for reconhecida como autorizada o display exibe “Acesso concedido”. O led verde acende,  o led vermelho apaga, e o servo motor é acionado para abrir a fechadura. Se o UID da Tag não estiver autorizada, o display exibirá “negado!”. O led vermelho permanece aceso e o sistema aguarda por segundos antes de retornar ao estado inicial.

Controle via Bluetooth:
O sistema permite controlar a fechadura remotamente usando comandos bluetooth recebidos pelo SoftwareSerial. Comandos aceitos ‘A’ que abre a fechadura (Servo move para a posição aberta)
‘F’	 fecha a fechadura (Servo retorna para a posição de trancado)
Este controle permite que o usuário desbloqueie ou bloqueie a fechadura remotamente.

Controle manual com botão:
Um botão no sistema permite o controle manual da fechadura. Se o botão for pressionado enquanto a fechadura estiver aberta, o sistema tranca a fechadura, acedendo o led vermelho e apagando o led verde.


