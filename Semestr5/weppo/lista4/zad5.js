process.stdout.write('Imie: ')

process.stdin.on('data', (chunk) => {
    console.log(`Witaj ${chunk.toString().replace('\n', '')}`)
    process.exit(0)
})