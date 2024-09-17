# Robô do Tipo Esteira com Mini-Braço Robótico

Este projeto é um robô do tipo esteira equipado com um mini-braço robótico, projetado para realizar pequenos desafios e colocar em prática conceitos de programação e robótica

## Materiais Usados

- Bateria NiMH 7.2V (ideal seria uma bateria de notebook, para usar em conjunto com o conversor DC-DC, que mantém a corrente estável e possibilita o ajuste da tensão).
- Motores com redução
- Engrenagens
- Barra roscada
- Porcas, parafusos e arruelas
- Roldanas de câmbio de bicicleta
- Corrente de bicicleta
- Ponte H L298N (é possível usar relés de 5V para controlar o sentido dos motores também)
- Arduino Mega e Uno
- Joysticks
- Servos motores
- Chapas de alumínio e PVC
- Jumpers
- RF24L01
- Conector de chuveiro (para prender a barra roscada)
- Cano de PVC

## Importante

- Compreender o funcionamento de servos motores, comunicação por rádio frequência com o módulo RF24L01 e controle de motores com ponte H L298N é essencial antes de conectar os componentes.
- Realize testes a cada modificação ou adição de componentes para garantir o funcionamento correto.

## Montagem

-Diagramas com a pinagem de cada módulo pode ser encontrados facilmente na internet.

## Dicas

-Não esquecer de conectar o negativo/terra em tudo que tenha alimentação externa e seja controlado pelo arduino(equipontencializar o circuito).
-É possível, dependendo da corrente, usar a alimentação de 5v de saída do módulo L298N, conectando ao Vin do arduino, por exemplo, para alimentá-lo sem depender de outra fonte de tensão inferior.


