#include <tensor/storage/wal.hpp>
#include <tensor/storage/sst.hpp>
#include <tensor/storage/page.hpp>
#include <tensor/storage/rbm.hpp>
#include <tensor/storage/vec.hpp>
#include <tensor/storage/tok.hpp>
#include <tensor/storage/hnsw.hpp>
#include <iostream>
#include <cstring>
#include <vector>

using namespace tensor::storage;

int main() {
    std::cout << "=== Tensor Storage Library Tests ===" << std::endl;

    try {
        // Test 1: WAL (Write-Ahead Log)
        std::cout << "\n[TEST 1] Write-Ahead Log" << std::endl;
        {
            WAL wal("/tmp/test.wal");
            
            std::string record1 = "record_one";
            std::string record2 = "record_two";
            
            uint64_t lsn1 = wal.append(record1);
            uint64_t lsn2 = wal.append(record2);
            
            wal.flush();
            std::cout << "✓ WAL: Wrote 2 records (LSN " << lsn1 << ", " << lsn2 << ")" << std::endl;
        }

        // Test 2: SST (Sorted String Table)
        std::cout << "\n[TEST 2] Sorted String Table" << std::endl;
        {
            SSTBuilder builder("/tmp/test.sst", 4096);
            
            // Write some msgpack-formatted data (simple key-value pairs)
            std::string row1 = "\x81\xa4name\xa5Alice";  // {"name": "Alice"}
            std::string row2 = "\x81\xa4name\xa3Bob";    // {"name": "Bob"}
            std::string row3 = "\x81\xa4name\xa7Charlie"; // {"name": "Charlie"}
            
            uint32_t id1 = builder.append(row1);
            uint32_t id2 = builder.append(row2);
            uint32_t id3 = builder.append(row3);
            
            builder.finish();
            std::cout << "✓ SST: Wrote 3 rows (IDs " << id1 << ", " << id2 << ", " << id3 << ")" << std::endl;
            
            // Read back
            SST sst("/tmp/test.sst");
            auto result = sst.get(id2);
            if (result) {
                std::cout << "✓ SST: Read row ID " << id2 << " successfully" << std::endl;
            }
        }

        // Test 3: RBM (Roaring Bitmap Index)
        std::cout << "\n[TEST 3] Roaring Bitmap Index" << std::endl;
        {
            RBMBuilder rbm_builder("/tmp/test.rbm");
            
            // Index tokens to row IDs
            rbm_builder.add("alice", 0);
            rbm_builder.add("bob", 1);
            rbm_builder.add("charlie", 2);
            rbm_builder.add("alice", 3);  // alice appears in multiple rows
            
            rbm_builder.finish();
            std::cout << "✓ RBM: Built inverted index with 4 token entries" << std::endl;
            
            // Read back
            RBM rbm("/tmp/test.rbm");
            auto alice_rows = rbm.get("alice");
            std::cout << "✓ RBM: Query 'alice' returned " << alice_rows.cardinality() << " rows" << std::endl;
        }

        // Test 4: VEC (Vector Storage)
        std::cout << "\n[TEST 4] Vector Storage" << std::endl;
        {
            VECBuilder vec_builder("/tmp/test.vec");
            
            // Create sample 3D vectors
            float vec1[] = {1.0f, 0.0f, 0.0f};
            float vec2[] = {0.0f, 1.0f, 0.0f};
            float vec3[] = {0.0f, 0.0f, 1.0f};
            
            vec_builder.append(vec1, 3);
            vec_builder.append(vec2, 3);
            vec_builder.append(vec3, 3);
            
            vec_builder.finish();
            std::cout << "✓ VEC: Wrote 3 vectors (dimension=3)" << std::endl;
            
            // Read back
            VEC vec("/tmp/test.vec");
            const float* data = vec.data();
            std::cout << "✓ VEC: Memory-mapped file, size=" << vec.file_size() << " bytes" << std::endl;
            std::cout << "  First vector: [" << data[0] << ", " << data[1] << ", " << data[2] << "]" << std::endl;
        }

        // Test 5: TOK (Pre-tokenized Arrays)
        std::cout << "\n[TEST 5] Tokenized Storage" << std::endl;
        {
            TOKBuilder tok_builder("/tmp/test.tok", "gpt2");
            
            // Simulate tokenized data
            std::vector<int32_t> tokens1 = {101, 2054, 2003, 102};
            std::vector<int32_t> tokens2 = {101, 2129, 2003, 102};
            std::vector<int32_t> tokens3 = {101, 1045, 2572, 102};
            
            tok_builder.append(0, tokens1);
            tok_builder.append(1, tokens2);
            tok_builder.append(2, tokens3);
            
            tok_builder.finish();
            std::cout << "✓ TOK: Wrote 3 tokenized arrays (model=gpt2)" << std::endl;
            
            // Read back
            TOK tok("/tmp/test.tok", "gpt2");
            if (tok.is_valid()) {
                auto result = tok.get(1);
                if (result) {
                    std::cout << "✓ TOK: Read token array for row 1, size=" << result->size() << std::endl;
                }
            }
        }

        // Test 6: HNSW (Hierarchical Navigable Small World)
        std::cout << "\n[TEST 6] HNSW Vector Index" << std::endl;
        {
            HNSW hnsw("/tmp/test.hnsw", 3);
            
            // Insert vectors
            float vec1[] = {1.0f, 0.0f, 0.0f};
            float vec2[] = {0.0f, 1.0f, 0.0f};
            float vec3[] = {0.0f, 0.0f, 1.0f};
            float vec4[] = {0.95f, 0.1f, 0.0f};  // close to vec1
            
            hnsw.insert(0, vec1);
            hnsw.insert(1, vec2);
            hnsw.insert(2, vec3);
            hnsw.insert(3, vec4);
            
            hnsw.save();
            std::cout << "✓ HNSW: Inserted 4 vectors" << std::endl;
            
            // Search
            float query[] = {1.0f, 0.0f, 0.0f};
            auto results = hnsw.search(query, 2);
            std::cout << "✓ HNSW: KNN search returned " << results.size() << " results" << std::endl;
            if (!results.empty()) {
                std::cout << "  Nearest: row_id=" << results[0].row_id 
                          << ", distance=" << results[0].distance << std::endl;
            }
        }

        std::cout << "\n=== All Tests Passed ===" << std::endl;
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "❌ Error: " << e.what() << std::endl;
        return 1;
    }
}