package main

import "fmt"

type Peca struct {
	codigo         uint32
	quantidade     uint32
	valor_unitario float64
}

func (peca *Peca) leitura() {
	fmt.Scan(&peca.codigo, &peca.quantidade, &peca.valor_unitario)
}

func (peca *Peca) valor_total() float64 {
	return float64(peca.quantidade) * peca.valor_unitario
}

func (peca *Peca) pagamento(outra_peca *Peca) {
	valor := peca.valor_total() + outra_peca.valor_total()

	fmt.Printf("VALOR A PAGAR: R$ %.2f\n", valor)
}

func main() {

	var peca_1, peca_2 Peca

	peca_1.leitura()
	peca_2.leitura()
	peca_1.pagamento(&peca_2)
}
