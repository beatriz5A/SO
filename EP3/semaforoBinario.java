import java.util.concurrent.Semaphore;

public class semaforoBinario {

	static Semaphore semaphore = new Semaphore(1);

	static class MinhaThread extends Thread {

		private String nome;
		private int tempo;
	
		//construtor que inicia a thread
		public MinhaThread(String nome, int tempo){
			this.nome = nome;
			this.tempo = tempo;
			start();
		}
	
		//metodo que executa a thread
		public void run(){
			
			System.out.println("---------------------------------------------------------------------");

			try{

				//verifica se existe um semaforo disponivel
				System.out.println("\nSemáforos disponíveis: " + semaphore.availablePermits());
				semaphore.acquire();

				System.out.println("Iniciando a execução da " + nome + "\n\n");

				try{

					//caso o semaforo esteja disponivel, a thread e executada
					System.out.println(nome + " na seção crítica\n");

					for (int i=0; i<4; i++){

						System.out.println("Semáforos disponíveis: " + semaphore.availablePermits());

						System.out.println(nome + " Hello World " + i);
						Thread.sleep(tempo);
					}

					//depois de executada a thread sai da secao critica
					System.out.println("\n\n" + nome + " na seção não crítica");

				} finally {

					//e o semaforo e liberado
					semaphore.release();
					System.out.println("Semáforos disponíveis: " + semaphore.availablePermits() + "\n\n");
				}

			} catch(InterruptedException e) {
				System.out.println("Erro ao adquirir permissão para a " + nome);
			}

			System.out.println("---------------------------------------------------------------------");


		}
	
	}
	public static void main(String[] args) {

		//inicia a execucao de 100 threads
		for(int i = 0; i < 100; i++){

			MinhaThread thread = new MinhaThread("Thread " + i, (i+1)*2);
		}
	}
}



