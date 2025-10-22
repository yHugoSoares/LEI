const todos = [];

/* Ex. 1: Add a event listener that triggers when the DOM is loaded here */
document.addEventListener('DOMContentLoaded', () => {
    const dateEl = document.getElementById('list-date');
    const options = { year: 'numeric', month: 'numeric', day: 'numeric' };
    dateEl.textContent = new Date().toLocaleDateString('pt-PT', options);
});


/* Ex. 2: Complete todo rendering */
// complete function to remove all child nodes
// arg parent is the node to clean
function removeAllChildNodes(parent) {
    while (parent.firstChild) {
        parent.removeChild(parent.firstChild);
    }
}



// render todo array here
function renderTodoList() {
    const listEl = document.getElementById('todo-list');
    if (!listEl) return;

    // limpa lista antes de renderizar
    removeAllChildNodes(listEl);

    todos.forEach((task, index) => {
        const li = document.createElement('li');
        li.className = 'todo-list-item';

        const p = document.createElement('p');
        p.textContent = task;

        const btn = document.createElement('button');
        btn.textContent = 'Delete';
        btn.dataset.index = index; // guarda o índice para remoção
        btn.addEventListener('click', removeTodoItem);

        li.appendChild(p);
        li.appendChild(btn);

        listEl.appendChild(li);
    });
}



/* Ex. 3: Add a event listener to element 'todo-form'*/
document.getElementById('todo-form').addEventListener('submit', event => {
    event.preventDefault();
    const input = document.getElementById('task-input');
    if (!input) return;

    const value = input.value.trim();
    if (!value) return;

    todos.push(value);
    input.value = '';
    input.focus();

    renderTodoList();
});




/* Ex. 4 and 5: complete delete button click logic */
// arg event is the triggered event (with event you can get the element clicked).
function removeTodoItem(event) {
    const btn = event.currentTarget;
    const idx = Number(btn.dataset.index);
    if (!Number.isFinite(idx)) return;

    todos.splice(idx, 1);
    renderTodoList();
}