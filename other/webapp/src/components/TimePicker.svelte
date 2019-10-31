<script>
	export let hour = 0;
    export let minute = 0;
    
    const hours = [];
    const minutes = [];

    for(let i = 0; i < 24; i++) {
        hours.push(i);
    }
    for(let i = 0; i < 60; i+=10) {
        minutes.push(i);
    }
</script>

<style>
	select {
        transition: all .3s;
        appearance: none;
        border: none;
        /* text-align-last: center;
        text-align-last: -webkit-center;
        text-align: center;
        text-align: -webkit-center; */
        padding-left: 23px;
        background: transparent;
        @apply font-bold;

        &:pocus {
            @apply text-teal-500;
        }
    }
</style>


<div class="time-picker bg-white rounded-lg m-3 h-12 w-32 flex flex-row flex-no-wrap items-center">
    <select class="flex-1 self-stretch" bind:value={hour}>
        {#each hours as h}
            <option value={h}>{h}</option>
        {/each}
    </select>
    <span>:</span>
    <select class="flex-1 self-stretch" bind:value={minute}>
        {#each minutes as m}
            <option value={m}>{m}</option>
        {/each}
    </select>
</div>