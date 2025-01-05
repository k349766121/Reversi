
import './App.css'
import axios from 'axios';
import React, { useState } from 'react';
const blank = 45;
const red = 87;
const blue = 66;
export default function App() {
  // Step 1: Capture the desired board size n
  const [boardSize, setBoardSize] = useState(4);

  function handleChange(e) {
    // Convert the input string to a number
    const newSize = parseInt(e.target.value, 10);
    // 4 is the smallest board size
    if (!isNaN(newSize) && newSize >= 4) {
      setBoardSize(newSize);
    }
  }

  return (
    <div>
      <h1 className="page-title">Reversi</h1>
      <Board n={boardSize} />
      <div className="board-controls">
        <label>
          Resize & Restart:
          <input
            type="number"
            value={boardSize}
            onChange={handleChange}
            min="4"
            step="2"
            className="board-input"
            onKeyDown={(e) => e.preventDefault()}
          />
        </label>
      </div>
      
     
    </div>
  );
}

function Board({ n }) {
  const [end_res, setEnd_res] = useState('NA');
  // Step 2: We’ll store the squares in a 1D array of size n*n
  const [squares, setSquares] = useState(Array(n * n).fill(blank));
  // If `n` changes, reset the state to match the new size
  React.useEffect(() => {
    const fetchData = async () => {
      try {
        const jsonData = await putRequest('new', n, 0); 
        setSquares(jsonData.display); // Update state with resolved data
        setEnd_res(jsonData.result);
      } catch (error) {
        console.error('Error fetching data:', error); // Handle errors
      }
    };
    fetchData();
  }, [n]);

  function handleClick(index) {
    const fetchData = async () => {
      try {
        const jsonData = await putRequest('play', Math.floor(index / n), index % n); 
        setSquares(jsonData.display); // Update state with resolved data
        setEnd_res(jsonData.result);
      } catch (error) {
        console.error('Error fetching data:', error); // Handle errors
      }
    };
    if (squares[index] == blank){
      fetchData();
    } 
  }

  return (
    <div>
      {/* Step 3: Render rows and columns based on n */}
      {Array.from({ length: n }).map((_, rowIndex) => (
        <div className="board-row" key={rowIndex}>
          {Array.from({ length: n }).map((_, colIndex) => {
            const index = rowIndex * n + colIndex;
            return (
              <Square
                key={index}
                value={squares[index]}
                onSquareClick={() => handleClick(index)}
              />
            );
          })}
        </div>
      ))}
      
      <Result end={end_res}/>
    </div>
  );
}
function Result({end}) {
  if (end == 'NA'){
    return null;
  } else {
    return <p className="result">{end}</p>
  }
}

function Square({ value, onSquareClick }) {
  
  let color;
  if (value == blank){
    color = 'grey';
  } else if (value == red) {
    color = 'red';
  } else if (value == blue){
    color = 'blue'; 
  }
  return (
    <button className="square" onClick={onSquareClick} style={{backgroundColor: color }}></button>
  );
  
}


async function putRequest(type, input1, input2) {
  const response = await axios.put(`http://localhost:18080/${type}/${input1}/${input2}`, {}, {
    headers: {
      "Content-Type": "application/json",
    },
  });
  return response.data;
};
