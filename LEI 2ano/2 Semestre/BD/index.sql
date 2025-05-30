-- Índice para buscas por datas de reserva
CREATE INDEX idx_reserva_data ON Reserva(data_inicio);

-- Índice composto para status + localização de veículos
CREATE INDEX idx_veiculo_status_local ON Veiculo(status, id_stand);

-- Índice para buscas de clientes por nome
CREATE INDEX idx_cliente_nome ON Cliente(nome);

-- Índice para histórico de manutenções
CREATE INDEX idx_manutencao_veiculo ON Manutencao(id_veiculo);