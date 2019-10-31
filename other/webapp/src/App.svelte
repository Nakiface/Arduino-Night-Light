<script>
	import {onMount} from 'svelte';
	import axios from 'axios';
	import TimePicker from './components/TimePicker.svelte'
	import {SlidersIcon, SunIcon, Trash2Icon} from 'svelte-feather-icons'

	let data;
	$: handleDataChange(data);

	let timeout;
	function handleDataChange(data) {
		console.log(data)
		if(timeout) clearTimeout(timeout);
		timeout = setTimeout(async () => {
			const response = await axios.post('/savesettings', data);
			console.log(response);
		}, 1000)
	}

	onMount(async () => {
		const response = await fetch("./settings.json");
		data = await response.json();
	})

	let active = 'settings';

	function removeLamp(index) {
		console.log(index);
		if(data) {
			data.LIFX.splice(index, 1);
		}
	}
</script>

<style lang="postcss">
label:not(:first-child) {
	@apply mt-4 text-center;
}

input[type="range"] {
	@apply m-3 w-32;

	&::track {
		@apply bg-white h-1 rounded-full;
	}

	&::thumb {
		@apply rounded-full w-3 h-5 bg-teal-500 shadow -mt-2;
	}

	&:pocus {
		outline: none;
	}
}

button.active {
	@apply text-teal-600;
}
</style>

<div class="flex flex-col min-h-screen text-gray-700">
	<main class="flex-1">
		<div class="container py-10 flex flex-col items-center">
				<h1 class="text-3xl md:text-6xl font-bold text-center">Smart Night Light</h1>
				<h2 class="text-sm md:text-2xl mb-10 text-center">powered by LIFX & ESP8266</h2>
				
				<div class="bg-gray-400 rounded-lg shadow-xl max-w-full">
					{#if data}
						<div class="flex flex-row flex-no-wrap h-20">
							<button class="h-full flex-1 p-6" class:active={active==='settings'} on:click={() => active='settings'}><SlidersIcon /></button>
							<button class="h-full flex-1 p-6" class:active={active==='lamps'} on:click={() => active='lamps'}><SunIcon /></button>
						</div>
						
						<div class="p-6 flex flex-col items-center">
						{#if active==='settings'}
							<label>
								When do you go to sleep?
							</label>
							<TimePicker bind:hour={data.nightStart.hour} bind:minute={data.nightStart.minute}/>
							
							<label>
								When do you wake up?
							</label>
							<TimePicker bind:hour={data.nightEnd.hour} bind:minute={data.nightEnd.minute}/>

							<label>
								How bright should the light be at night?
							</label>
							<input type="range" min="1" max="5" bind:value={data.nightBrightness} />
						
						{:else if active==='lamps'}
							<div>Currently readonly</div>
							{#each data.LIFX as lamp, index}
								<div class="time-picker bg-white rounded-lg m-3 px-6 h-12 w-full flex flex-row flex-no-wrap items-center justify-between">
									<span>{lamp.mac}</span>
									<span>{lamp.ip}</span>
									<!-- <input class="text-xs md:text-base flex-1" type="text" bind:value={lamp.mac} maxlength="17" />
									<input class="text-xs md:text-base flex-1" type="text" bind:value={lamp.ip} maxlength="15" />
									<button class="h-12 w-12 py-3" on:click={removeLamp(index)}><Trash2Icon /></button> -->
								</div>
							{/each}
						{/if}
						</div>
						
					{:else}
						Loading...
					{/if}
				</div>
		</div>
	</main>
	
	<footer class="w-screen bg-gray-900 text-white text-center text-xs md:text-base">
		<div class="container py-6">
			Made with &#10084; by Bernhard, Marvin, Fabian & Tom
		</div>
	</footer>
</div>