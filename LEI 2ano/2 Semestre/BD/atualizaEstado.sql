DELIMITER //
CREATE TRIGGER after_reserva_insert
AFTER INSERT ON Reserva
FOR EACH ROW
BEGIN
    CALL AtualizarStatusVeiculo(NEW.id_veiculo, 'Alugado');
END //
DELIMITER ;