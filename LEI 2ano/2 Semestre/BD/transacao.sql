DELIMITER //
CREATE PROCEDURE AtualizarStatusVeiculo(
    IN veiculo_id INT,
    IN novo_status VARCHAR(20)
)
BEGIN
    START TRANSACTION;
    UPDATE Veiculo SET status = novo_status WHERE id = veiculo_id;
    INSERT INTO Auditoria (acao, tabela, registro_id)
    VALUES ('UPDATE', 'Veiculo', veiculo_id);
    COMMIT;
END //
DELIMITER ;