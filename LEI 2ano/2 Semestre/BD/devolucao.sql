DELIMITER //
CREATE TRIGGER after_devolucao_insert
AFTER INSERT ON Devolucao
FOR EACH ROW
BEGIN
    -- Atualiza status do veículo
    CALL AtualizarStatusVeiculo(NEW.id_veiculo, 'Disponível');
    
    -- Registra quilometragem
    UPDATE Veiculo 
    SET quilometragem = quilometragem + NEW.km_percorridos
    WHERE id = NEW.id_veiculo;
END //
DELIMITER ;