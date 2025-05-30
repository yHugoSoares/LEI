DELIMITER //
CREATE FUNCTION CalcularValorReserva(
    veiculo_id INT,
    dias INT
) RETURNS DECIMAL(10,2)
BEGIN
    DECLARE preco_diario DECIMAL(10,2);
    
    SELECT tv.preco_diario INTO preco_diario
    FROM Veiculo v
    JOIN TipoVeiculo tv ON v.id_tipo_veiculo = tv.id
    WHERE v.id = veiculo_id;
    
    RETURN preco_diario * dias;
END //
DELIMITER ;