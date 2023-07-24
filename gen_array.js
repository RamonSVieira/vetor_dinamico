const fs = require('fs');

function generateArray(n) {
  const randomArray = [];
  for (let i = 0; i < n; i++) {
    randomArray.push(Math.floor(Math.random() * 1000)); // Gera números aleatórios entre 0 e 999
  }
  return randomArray;
}

function generateFile(filename, n) {
  const randomArray = generateArray(n);
  const fileContent = `${n}\n${randomArray.join(' ')}`;

  fs.writeFile(filename, fileContent, (err) => {
    if (err) {
      console.error('Error writing to file:', err);
    } else {
      console.log(`File '${filename}' with ${n} numbers generated successfully.`);
    }
  });
}

// Verificar se o número de argumentos é válido
if (process.argv.length !== 4) {
  console.error('Usage: node gen_array.js <output_file_name> <n>');
  process.exit(1);
}

const outputFile = process.argv[2];
const n = parseInt(process.argv[3]);

// Verificar se n é um número válido
if (isNaN(n) || n <= 0) {
  console.error('Invalid value of n. Please provide a positive integer.');
  process.exit(1);
}

generateFile(outputFile, n);
