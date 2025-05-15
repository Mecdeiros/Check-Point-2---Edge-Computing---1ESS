# Check-Point-2---Edge-Computing---1ESS

# Monitor Ambiental com Arduino e LCD I2C

Este projeto consiste em um sistema de monitoramento ambiental utilizando Arduino, com sensores de temperatura, umidade e luminosidade. As informações são exibidas em um display LCD 16x2 com interface I2C, e os LEDs coloridos (verde, amarelo e vermelho), juntamente com um buzzer, sinalizam visual e sonoramente as condições ambientais.

# Visão Geral

O sistema realiza a leitura de:
- Temperatura (usando o sensor DHT22)
- Umidade relativa do ar (DHT22)
- Intensidade luminosa (LDR)

Com base nessas leituras, o sistema:
- Exibe as informações no display LCD
- Aciona LEDs e buzzer para alertas visuais e sonoros, conforme os níveis detectados

# Componentes Utilizados

| Componente           | Descrição                       |
|----------------------|---------------------------------|
| Arduino UNO          | Microcontrolador principal      |
| DHT22                | Sensor de temperatura e umidade |
| LDR                  | Sensor de luminosidade          |
| LCD 16x2 (I2C)       | Exibição das leituras           |
| LED Verde            | Indicação de ambiente escuro    |
| LED Amarelo          | Indicação de valores limítrofes |
| LED Vermelho         | Indicação de valores críticos   |
| Buzzer               | Alarme sonoro                   |
| Resistores           | Para LEDs e LDR                 |
| Jumpers e Protoboard | Conexões                        |

# Funcionamento do Código

O sistema opera em um loop contínuo com três etapas principais:

# 1. Temperatura
- Mede a média de 5 leituras.
- Exibe a temperatura no LCD.
- Se:
  - < 10 °C → LED Amarelo + Buzzer (Temperatura Baixa)
  - 10–15 °C → Nenhum alerta (Temperatura OK)
  - > 15 °C → LED Amarelo + Buzzer (Temperatura Alta)

# 2. Umidade
- Mede a média de 5 leituras.
- Exibe a umidade no LCD.
- Se:
  - < 50% → LED Vermelho + Buzzer (Umidade Baixa)
  - 50–70% → Nenhum alerta (Umidade OK)
  - > 70% → LED Vermelho + Buzzer (Umidade Alta)

# 3. Luminosidade
- Mede a média de 5 leituras do LDR.
- Exibe a condição de luz no LCD.
- Se:
  - < 400 → LED Verde (Ambiente Escuro)
  - 400–600 → LED Amarelo (Meia Luz)
  - > 600 → LED Vermelho + Buzzer (Ambiente Muito Claro)

# Outros Detalhes
- O display LCD é limpo (`lcd.clear()`) após cada categoria de leitura.
- Todos os LEDs e buzzer são desligados no início de cada ciclo usando `desligaTodos()`.


# Considerações

- O uso de médias ajuda a reduzir leituras instáveis.
- O sistema é ideal para aplicações educacionais e projetos que envolvam conforto ambiental ou automação residencial básica.
- A separação de funções (leitura, média, exibição e alerta) torna o código modular e fácil de manter.

# Instruções de Montagem

1. Conecte o DHT22 ao pino digital 7.
2. Conecte o LDR ao pino A0, com resistor de pull-down.
3. Conecte os LEDs aos pinos 2 (verde), 3 (amarelo) e 4 (vermelho) com resistores.
4. Conecte o buzzer ao pino 9.
5. Conecte o LCD I2C aos pinos SDA (A4) e SCL (A5).
6. Faça o upload do código e abra o Monitor Serial (opcional) para depuração.

# Bibliotecas Necessárias

Instale estas bibliotecas na IDE do Arduino:

- `LiquidCrystal_I2C`
- `DHT sensor library`
- `Adafruit Unified Sensor`

# Links Projeto/Repositório
[Wokwi](https://wokwi.com/projects/430956393635725313)
[GitHub](https://github.com/Mecdeiros/Check-Point-2---Edge-Computing---1ESS)

# Imagem do Circuito 

![Image](https://github.com/user-attachments/assets/767fc4f5-a59f-422e-a6df-c6eaa8cd7f83)

# ✅ Conclusão

Este projeto demonstra a integração de sensores com feedback visual e sonoro em tempo real. É uma excelente introdução ao uso de sensores analógicos e digitais com Arduino, além de boas práticas como leitura média e organização modular de código.

# Integrantes 

- Guilherme de Medeiros           RM 561699
- Mikael de Albuquerque Santana   RM 566507
- Murilo Cruz                     RM 563743
- Otavio Magno da Silva           RM 566149
- Victor Pucci                    RM 561736
