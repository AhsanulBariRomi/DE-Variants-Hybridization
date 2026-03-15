# Hybrid Differential Evolution (DE) via Island Model

[![IEEE Publication](https://img.shields.io/badge/IEEE-Published_Paper-blue)](https://ieeexplore.ieee.org/document/11022468)

This repository contains a modified version of the original Differential Evolution (DE) algorithm in C. In 2019, this program was modified by **Md Ahsanul Bari (Romi)** to test the hybridization of two distinct DE strategies using an **Island Model framework**. 

This code served as the foundational proof-of-concept for the research presented in the paper:  
> **"A Case Study on Hybridizing Differential Evolution Variants in The Field of Optimization Using Benchmark Functions"** > *2024 27th International Conference on Computer and Information Technology (ICCIT)*

🔗 **[Read the full paper on IEEE Xplore](https://ieeexplore.ieee.org/document/11022468)**

---

## 📌 Background and Modifications

The base code is **Differential Evolution Version 3.6**, originally authored by **Dr. Rainer Storn and Kenneth Price**, the inventors of the DE algorithm. (Visual Studio 2010 updates were later provided by Charles Brauer). 

Traditional DE variants often struggle with premature convergence and maintaining the delicate balance between exploration and exploitation in multimodal landscapes. 

**The 2019 Modifications:**
To address these optimization challenges, the code was modified to introduce an **Island Model framework**. The population is divided into multiple independent sub-populations (islands), each running different DE strategies. Periodically, individuals migrate between islands to exchange information, preventing premature convergence and boosting diversity.

### 🧬 Hybridized Strategies
The implementation explores hybridizing combinations of the following DE variants:
* `DE/best/1/exp`
* `DE/rand/1/exp`
* `DE/best/1/bin`
* `DE/rand/1/bin`

### 🔄 Migration Mechanisms
Three specific information-sharing (migration) strategies were implemented:
1. **Rand to Rand Migration 1:** One randomly selected individual from each sub-population is exchanged.
2. **Rand to Rand Migration 2:** Two randomly selected individuals are exchanged between sub-populations.
3. **Best to Rand Migration 1:** The best individual from one sub-population is swapped with a random individual from another.

### 🧪 Benchmark Functions
The algorithms within this code were tested against five standard continuous optimization benchmark functions:
* **Sphere** (Unimodal)
* **Schwefel** (Multimodal)
* **Rastrigin** (Highly Multimodal)
* **Griewank** (Multimodal)
* **Michalewicz** (Steep valleys and ridges)

---

## ⚠️ Disclaimer

> *Note: This modified code was built in 2019 as an experimental proof-of-concept. It is not fully optimized for production environments and serves primarily as a demonstration of the Island Model hybridization concept. It should be used for educational and research purposes only.*

---

## 📖 Citation

If you find this code or the underlying research helpful for your work, please consider citing the associated paper:

```bibtex
@inproceedings{bari2024case,
  title={A Case Study on Hybridizing Differential Evolution Variants in The Field of Optimization Using Benchmark Functions},
  author={Bari, Md Ahsanul and Mithila, Afrina Zahan and Alam, Mohammad Shafiul},
  booktitle={2024 27th International Conference on Computer and Information Technology (ICCIT)},
  year={2024},
  organization={IEEE},
  doi={10.1109/ICCIT62916.2024.11022468}
}
```
---
## 🙌 Acknowledgments

* **Dr. [cite_start]Rainer Storn and Kenneth Price:** For inventing Differential Evolution [cite: 16] [cite_start]and making their original `de.c` (version 3.6) code publicly available[cite: 544].
* **Charles Brauer:** For the Visual Studio 2010 compatibility updates.
* [cite_start]**Co-authors:** Afrina Zahan Mithila and Mohammad Shafiul Alam for their valuable contributions to the 2024 paper[cite: 3].

---
## 👨‍💻 Author

**Md Ahsanul Bari (Romi)** * **Email:** wakerbari@gmail.com
* **GitHub:** [@AhsanulBariRomi](https://github.com/AhsanulBariRomi)
* **Affiliations:** * Technische Universität Dresden, Germany
  * Ahsanullah University of Science and Technology, Bangladesh
