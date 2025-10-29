/*
  Exposed functions:
  - initBoard
  - handleCellClick
  - resetGame
  - checkWinner
  - updateStatus
*/

let board = Array(9).fill('');
let currentPlayer = 'X';
let gameOver = false;


function initBoard() {
  const cells = document.querySelectorAll('.cell');
  cells.forEach(cell => {
    cell.textContent = '';
    cell.classList.remove('x','o');
    // ensure we don't attach the same handler multiple times on reset
    cell.removeEventListener('click', handleCellClick);
    cell.addEventListener('click', handleCellClick);
  });

  board = Array(9).fill('');
  currentPlayer = 'X';
  gameOver = false;
  updateStatus();
}


function handleCellClick(evt) {
  const idx = Number(evt.currentTarget.dataset.index);
  if (gameOver) {
    window.alert('Jogo Terminado! Faça reset para recomeçar.');
    return;
  }
  if (board[idx]) {
    window.alert('Célula já preenchida');
    return;
  }

  board[idx] = currentPlayer;
  const cell = evt.currentTarget;
  cell.textContent = currentPlayer;
  cell.classList.add(currentPlayer.toLowerCase());

  const winner = checkWinner(board);
  if (winner === 'X' || winner === 'O') {
    updateStatus(`${winner} venceu`);
    gameOver = true;
    window.alert(`Vencedor: ${winner}`);
    return;
  } else if (winner === 'draw') {
    updateStatus('Empate');
    gameOver = true;
    window.alert('Empate');
    return;
  }

  currentPlayer = currentPlayer === 'X' ? 'O' : 'X';
  updateStatus();
}

function resetGame() {
  initBoard();
}

function updateStatus(text) {
  const statusEl = document.getElementById('status');
  if (!statusEl) return;
  if (text) {
    statusEl.textContent = text;
  } else {
    statusEl.textContent = `Turno: ${currentPlayer}`;
  }
}

/*
  checkWinner(board)
  returns:
    - 'X' or 'O' when there's a winner
    - 'draw' when board full and no winner
    - null otherwise
*/
function checkWinner(b) {
  const combos = [
    [0,1,2],[3,4,5],[6,7,8], // rows
    [0,3,6],[1,4,7],[2,5,8], // cols
    [0,4,8],[2,4,6]          // diags
  ];

  for (const [a,bidx,c] of combos) {
    if (b[a] && b[a] === b[bidx] && b[a] === b[c]) {
      return b[a];
    }
  }

  if (b.every(cell => cell)) return 'draw';
  return null;
}

/* init on DOM ready */
document.addEventListener('DOMContentLoaded', () => {
  initBoard();

  const resetBtn = document.getElementById('reset');
  if (resetBtn) resetBtn.addEventListener('click', resetGame);
});