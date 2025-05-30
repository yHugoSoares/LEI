-- 1. Veículos disponíveis no Porto
SELECT v.matricula, v.modelo, tv.designacao AS tipo
FROM Veiculo v
JOIN TipoVeiculo tv ON v.id_tipo_veiculo = tv.id
JOIN Stand s ON v.id_stand = s.id
WHERE s.localizacao = 'Porto'
  AND v.status = 'Disponível';

-- 2. Reservas do cliente 'João Silva'
SELECT r.id, r.data_inicio, r.data_fim, v.matricula
FROM Reserva r
JOIN Cliente c ON r.id_cliente = c.id
JOIN Veiculo v ON r.id_veiculo = v.id
WHERE c.nome = 'João Silva';

-- 3. Faturação por tipo de veículo (últimos 30 dias)
SELECT tv.designacao, SUM(r.custo) AS total
FROM Reserva r
JOIN Veiculo v ON r.id_veiculo = v.id
JOIN TipoVeiculo tv ON v.id_tipo_veiculo = tv.id
WHERE r.data_inicio >= CURDATE() - INTERVAL 30 DAY
GROUP BY tv.id;

-- 4. Manutenções pendentes
SELECT v.matricula, m.descricao, m.data_prevista
FROM Manutencao m
JOIN Veiculo v ON m.id_veiculo = v.id
WHERE m.status = 'Pendente';

-- 5. Veículos mais rentáveis
SELECT v.matricula, SUM(r.custo) AS faturado
FROM Veiculo v
JOIN Reserva r ON v.id = r.id_veiculo
GROUP BY v.id
ORDER BY faturado DESC
LIMIT 5;