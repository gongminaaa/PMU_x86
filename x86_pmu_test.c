#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#define EVTCOUNT 4

static void set_pce(void *arg)
{
	int to_val = (arg != 0);
	unsigned int cr4_val;

	cr4_val = __read_cr4();
	printk("cr4_val: %08x\n", cr4_val);
	if(to_val) {
		cr4_val |= X86_CR4_PCE;
	} else {
		cr4_val &= ~X86_CR4_PCE;
	}
	printk("cr4_val: %08x\n", cr4_val);

	__write_cr4(cr4_val);
}


static int __init user_rdpmc_init(void){
	unsigned int msr;
	unsigned int low, high;
	unsigned int mem_evtsel_low[EVTCOUNT] = {0};
	unsigned int mem_evtsel_high[EVTCOUNT] = {0};
	unsigned int i=0;
	unsigned int a=0;

	unsigned int num_cpus=0;
	int cpu;

	num_cpus = num_online_cpus();

	printk(KERN_INFO "Enabling RDPMC %d CPUs\n", num_cpus);
	for(cpu = 0; cpu<num_cpus; cpu++) {
		smp_call_function_single(cpu, set_pce, (void *)1, 1);
	}

	/*******************************************
	 * IA32_PERF_GLOBAL_CTRL setting
	 *******************************************/
	msr = 0x38F;
	rdmsr(msr, low, high);
	printk("##READ BEFORE SETTING## IA32_PERF_GLOBAL_CTRL 0x38F: [low]%08x, [high]%08x\n", low, high);

	low |= 0xF;
	wrmsr(msr, low, high);
	printk("##WRITE## IA32_PERF_GLOBAL_CTRL 0x38F: [low]%08x, [high]%08x\n", (low), (high));

	rdmsr(msr, low, high);
	printk("##READ## IA32_PERF_GLOBAL_CTRL 0x38F: [low]%08x, [high]%08x\n", (low), (high));


	//		[PERF_COUNT_HW_CPU_CYCLES]              = 0x003c,
	//		[PERF_COUNT_HW_INSTRUCTIONS]            = 0x00c0,
        //		[PERF_COUNT_HW_CACHE_REFERENCES]        = 0x4f2e,
        //		[PERF_COUNT_HW_CACHE_MISSES]            = 0x412e,
        //		[PERF_COUNT_HW_BRANCH_INSTRUCTIONS]     = 0x00c4,
        //		[PERF_COUNT_HW_BRANCH_MISSES]           = 0x00c5,
        //		[PERF_COUNT_HW_BUS_CYCLES]              = 0x013c,
        //		[PERF_COUNT_HW_REF_CPU_CYCLES]          = 0x0300, /* pseudo-encoding */
	     
	/*******************************************
	 * IA32_PERFEVTSELx MSR setting
	*******************************************/


	/*******************************************
	 * IA32_PERFEVTSEL0: instructions
	 *******************************************/
	 msr = 0x186;
	 rdmsr(msr, mem_evtsel_low[0], mem_evtsel_high[0]);
	 printk("##READ BEFORE SETTING## IA32_PERFEVTSEL0 0x186: [low]%08x, [high]%08x\n", (mem_evtsel_low[0]), (mem_evtsel_high[0]));
	 low = 0x4300c0;
	 high = mem_evtsel_high[0] | 0x0;
	 wrmsr(msr, low, high);
	 printk("##WRITE## IA32_PERFEVTSEL0 0x186: [low]%08x, [high]%08x\n", (low), (high));
	
	 rdmsr(msr, low, high);
	 printk("##READ## IA32_PERFEVTSEL0 0x186: [low]%08x, [high]%08x\n", (low), (high));
	     
	 /*******************************************
	  * IA32_PERFEVTSEL1: Cache References
	  *******************************************/
	 msr = 0x187;
	 rdmsr(msr, mem_evtsel_low[1], mem_evtsel_high[1]);
	 printk("##READ BEFORE SETTING## IA32_PERFEVTSEL1 0x187: [low]%08x, [high]%08x\n", (mem_evtsel_low[1]), (mem_evtsel_high[1]));
	 low = 0x434f2e;
	 high = mem_evtsel_high[1] | 0x0;
	 wrmsr(msr, low, high);
	 printk("##WRITE## IA32_PERFEVTSEL1 0x187: [low]%08x, [high]%08x\n", (low), (high));
	
	 rdmsr(msr, low, high);
	 printk("##READ## IA32_PERFEVTSEL1 0x187: [low]%08x, [high]%08x\n", (low), (high));

	     
	 /*******************************************
	  * IA32_PERFEVTSEL2: Branch Misses
	  *******************************************/
	 msr = 0x188;
	 rdmsr(msr, mem_evtsel_low[2], mem_evtsel_high[2]);
	 printk("##READ BEFORE SETTING## IA32_PERFEVTSEL2 0x188: [low]%08x, [high]%08x\n", (mem_evtsel_low[2]), (mem_evtsel_high[2]));
	 low = 0x4300c5;
	 high = mem_evtsel_high[2] | 0x0;
	 wrmsr(msr, low, high);
	 printk("##WRITE## IA32_PERFEVTSEL2 0x188: [low]%08x, [high]%08x\n", (low), (high));
	
	 rdmsr(msr, low, high);
	 printk("##READ## IA32_PERFEVTSEL2 0x188: [low]%08x, [high]%08x\n", (low), (high));


	 /*******************************************
	  * IA32_PERFEVTSEL3: Cache Misses
	  *******************************************/
	 msr = 0x189;
	 rdmsr(msr, mem_evtsel_low[3], mem_evtsel_high[3]);
	 printk("##READ BEFORE SETTING## IA32_PERFEVTSEL3 0x189: [low]%08x, [high]%08x\n", (mem_evtsel_low[3]), (mem_evtsel_high[3]));
	 low = 0x43412e;
	 high = mem_evtsel_high[3] | 0x0;
	 wrmsr(msr, low, high);
	 printk("##WRITE## IA32_PERFEVTSEL3 0x189: [low]%08x, [high]%08x\n", (low), (high));
	
	 rdmsr(msr, low, high);
	 printk("##READ## IA32_PERFEVTSEL3 0x189: [low]%08x, [high]%08x\n", (low), (high));
	     


	 /*******************************************
	  * IA32_PMCx reset to 0 to start counting
	  *******************************************/
	 msr = 0xC1;
	 low = 0x0;
	 high = 0x0;

	 for(i=0; i<EVTCOUNT; i++) {
		wrmsr(msr, low, high);
		++msr;
	 }
#if 1
	 for(i=0; i<99999; i++)
	 {
		a++;
	 }
#endif
  
	 low = 0, high = 0;

	 /*******************************************
	 * IA32_PERF_EVTSELx register
	 * BIT22: Enable Counters (Disabled)
	 *******************************************/
	 msr = 0x186; // EVTSEL register
	 for(i=0; i<EVTCOUNT; i++) {
		wrmsr(msr, mem_evtsel_low[i], mem_evtsel_high[i]);
		++msr;
	 }


	 /***************************************************
	 * IA32_PERF_GLOBAL_CONTROL register: PMC disable
	 ****************************************************/
	 msr = 0x38F;
	 wrmsr(msr, low, high);

	 /*******************************************
	 * IA32_PMCx reading
	 *******************************************/
	 msr = 0xc1;
	 for(i=0; i<EVTCOUNT; i++) {
		rdmsr(msr, low, high);
		printk("##READ ##3## IA32_PMC%d 0x%02x: [low]%u, [high]%u\n", i, msr, low, high);
		++msr;
	 }

	 printk("a: %d\n", a);

	 msr = 0x186;
	 for(i=0; i<EVTCOUNT; i++) {
		rdmsr(msr, low, high);
		printk("@@CLEAR BITS@@ IA32_PERF_EVTSEL%d 0x%03x: [low]%08x, [high]%08x\n", i, msr, low, high);
	 }

	 /****************************************************
	  * IA32_PERF_GLOBAL_STATUS check PMCs overflow
	  ****************************************************/
 	  msr = 0x38E;
	  rdmsr(msr, low, high);
	  printk("##CHECK OVERFLOW## IA32_PERF_GLOBAL_STATUS 0x38F: [low]%08x, [high]%08x\n", low, high);

	 /****************************************************
	  * IA32_PERF_GLOBAL_CONTROL check reset bits
	  ****************************************************/
	  msr = 0x38F; // GLOBAL_CTRL register
	  rdmsr(msr, low, high);
	  printk("@@CLEAR BITS@@ IA32_PERF_GLOBAL_CTRL 0x38F: [low]%08x, [high]%08x\n", (low), (high));

     return  0;

}

static void __exit user_rdpmc_exit(void)
{
    	printk(KERN_INFO "Disabling RDPMC from ring 3 for CPUs\n");
}

module_init(user_rdpmc_init);
module_exit(user_rdpmc_exit);
